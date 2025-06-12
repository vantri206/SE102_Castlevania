#include "Collision.h"
#include "GameObject.h"

#include "debug.h"
#include "GameDefine.h"
#include "Weapon.h"
#include "Ghoul.h"

#define BLOCK_PUSH_FACTOR 0.1f

CCollision* CCollision::__instance = NULL;

CCollision* CCollision::GetInstance()
{
	if (__instance == NULL) __instance = new CCollision();
	return __instance;
}
/*
	Overlap Collision
*/
void CCollision::Overlap(
	float l1, float t1, float r1, float b1,
	float l2, float t2, float r2, float b2,
	float x1, float x2, float y1, float y2,
	float& t, float& nx, float& ny)
{
	t = -1.0f;
	nx = ny = 0.0f;

	if (r1 <= l2 || l1 >= r2 || b1 >= t2 || t1 <= b2)	return;

	t = 0.0f;


	float overlapX = min(r1, r2) - max(l1, l2);
	float overlapY = min(t1, t2) - max(b1, b2);


	float dx = x2 - x1;
	float dy = y2 - y1;

	if (overlapX < overlapY)	//overlap theo x
	{
		if (dx > 0)
			nx = -1.0f;		//obj1 left to obj2
		else if (dx < 0)
			nx = 1.0f;		//obj1 right to obj2
	}
	else						//overlap theo y
	{
		if (dy > 0)
			ny = -1.0f;  // obj1 below obj2
		else if (dy < 0)
			ny = 1.0f;   // obj1 on top obj2
	}
}

LPCOLLISIONEVENT CCollision::Overlap(LPGAMEOBJECT objSrc, LPGAMEOBJECT objDest)
{
	float sl, st, sr, sb; 
	float dl, dt, dr, db;
	float sx, sy;
	float dx, dy;
	objSrc->GetBoundingBox(sl, st, sr, sb);
	objDest->GetBoundingBox(dl, dt, dr, db);
	objSrc->GetPosition(sx, sy);
	objDest->GetPosition(dx, dy);

	float t, nx, ny;

	Overlap(sl, st, sr, sb, dl, dt, dr, db, sx, dx, sy, dy, t, nx, ny);
	CCollisionEvent* e = nullptr;

	if (t < 0.0f || t > 1.0f) return nullptr;

	e = new CCollisionEvent(t, nx, ny, 0.0f, 0.0f, objDest, objSrc);
	return e;
}
/*
	SweptAABB
*/
void CCollision::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float& t, float& nx, float& ny)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt + dy : mt;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb: mb + dy;

	if (br < sl || bl > sr || bb > st || bt < sb) return;

	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision
	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}
	if (dy < 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy > 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}
	
	if (dx == 0)
	{
		tx_entry = -9999999.0f;
		tx_exit = 99999999.0f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999.0f;
		ty_exit = 99999999999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}

	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;
	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CCollision::SweptAABB(LPGAMEOBJECT objSrc, DWORD dt, LPGAMEOBJECT objDest)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	float mvx, mvy;
	objSrc->GetSpeed(mvx, mvy);
	float mdx = mvx * dt;
	float mdy = mvy * dt;

	float svx, svy;
	objDest->GetSpeed(svx, svy);
	float sdx = svx * dt;
	float sdy = svy * dt;

	//
	// NOTE: new m speed = original m speed - collide object speed
	// 
	float dx = mdx - sdx;
	float dy = mdy - sdy;	//dy < 0: going down, dy > 0: going up

	objSrc->GetBoundingBox(ml, mt, mr, mb);
	objDest->GetBoundingBox(sl, st, sr, sb);

	SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);
	if (t < 0.0f || t > 1.0f) return nullptr;
	return new CCollisionEvent(t, nx, ny, dx, dy, objDest, objSrc);
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CCollision::Scan(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* objDests, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < objDests->size(); i++)
	{
		LPGAMEOBJECT objDest = objDests->at(i);
		if (objDest == objSrc) continue; 
		if (!objSrc->CanCollisionWithObj(objDest)) continue;
		LPCOLLISIONEVENT e = nullptr;
		e = SweptAABB(objSrc, dt, objDest);
		if (e && e->WasCollided() == 1)
			coEvents.push_back(e);
		else e = nullptr;
		if (e != nullptr) continue;		//has dynamic collsion
		if (!objSrc->CanOverlapWithObj(objDest)) continue;
			if (objSrc->IsOverlappable() && (!objDest->IsBlocking() || (objDest->IsBlocking() && objDest->IsOverlappable())))
				e = Overlap(objSrc, objDest);
		if (e && e->WasCollided() == 1)
			coEvents.push_back(e);
		else
		{
			delete e;
			e = nullptr;
		}
	}
}

void CCollision::Filter(LPGAMEOBJECT objSrc,
	vector<LPCOLLISIONEVENT>& coEvents,
	LPCOLLISIONEVENT& colX,
	LPCOLLISIONEVENT& colY,
	int filterBlock = 1,		// 1 = only filter block collisions, 0 = filter all collisions 
	int filterX = 1,			// 1 = process events on X-axis, 0 = skip events on X 
	int filterY = 1)			// 1 = process events on Y-axis, 0 = skip events on Y
{
	float min_tx, min_ty;

	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];
		if (!c) continue;
		if (c->isDeleted) continue;
		if (c->obj->IsDeleted()) continue;

		if (filterBlock && !c->obj->IsBlocking()) continue;

		if (c->t < min_tx && c->nx != 0 && filterX == 1) {
			min_tx = c->t; min_ix = i;
		}

		if (c->t < min_ty && c->ny != 0 && filterY == 1)
		{
			min_ty = c->t; min_iy = i;
		}
	}

	if (min_ix >= 0) colX = coEvents[min_ix];
	if (min_iy >= 0) colY = coEvents[min_iy];
}

/*
*  Simple/Sample collision framework
*  NOTE: Student might need to improve this based on game logic
*/
void CCollision::Process(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	LPCOLLISIONEVENT colX = NULL;
	LPCOLLISIONEVENT colY = NULL;

	coEvents.clear();

	if (objSrc->IsCollidable())
	{
		Scan(objSrc, dt, coObjects, coEvents);
	}
	// No collision detected
	if (coEvents.size() == 0)
	{
		objSrc->OnNoCollision(dt);
	}
	else
	{
		Filter(objSrc, coEvents, colX, colY);
		float x, y, vx, vy, dx, dy;
		objSrc->GetPosition(x, y);
		objSrc->GetSpeed(vx, vy);
		dx = vx * dt;
		dy = vy * dt;
		if (colX != NULL && colY != NULL)
		{
			if (colY->t < colX->t)	// was collision on Y first ?
			{
				y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
				objSrc->SetPosition(x, y);

				objSrc->OnCollisionWith(colY);

				//
				// see if after correction on Y, is there still a collision on X ? 
				//
				LPCOLLISIONEVENT colX_other = NULL;

				//
				// check again if there is true collision on X 
				//
				colX->isDeleted = true;		// remove current collision event on X

				// replace with a new collision event using corrected location 
				coEvents.push_back(SweptAABB(objSrc, dt, colX->obj));

				// re-filter on X only
				Filter(objSrc, coEvents, colX_other, colY, /*filterBlock = */ 1, 1, /*filterY=*/0);

				if (colX_other != NULL)
				{
					x += colX_other->t * dx + colX_other->nx * BLOCK_PUSH_FACTOR;
					objSrc->OnCollisionWith(colX_other);
				}
				else
				{
					x += dx;
				}
			}
			else // collision on X first
			{
				x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
				objSrc->SetPosition(x, y);
				objSrc->OnCollisionWith(colX);

				//
				// see if after correction on X, is there still a collision on Y ? 
				//
				LPCOLLISIONEVENT colY_other = NULL;

				//
				// check again if there is true collision on Y
				//
				colY->isDeleted = true;		// remove current collision event on Y

				// replace with a new collision event using corrected location 
				coEvents.push_back(SweptAABB(objSrc, dt, colY->obj));

				// re-filter on Y only
				Filter(objSrc, coEvents, colX, colY_other, /*filterBlock = */ 1, /*filterX=*/0, /*filterY=*/1);

				if (colY_other != NULL)
				{
					y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
					objSrc->OnCollisionWith(colY_other);
				}
				else
				{
					y += dy;
				}
			}
		}
		else
		if (colX != NULL)
		{
			x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
			y += dy;
			objSrc->OnCollisionWith(colX);
		}
		else
		if (colY != NULL)
		{
			x += dx;
			y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
			objSrc->OnCollisionWith(colY);
		}
		else // both colX & colY are NULL 
		{
				x += dx;
				y += dy;
		}
		objSrc->SetPosition(x, y);
	}

	//
	// Scan all non-blocking collisions for further collision logic
	//
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (!e) continue;
		if (e->isDeleted) continue;
		if (e->obj->IsBlocking()) continue; 
		objSrc->OnCollisionWith(e);
	}


	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

int CCollisionEvent::WasCollided()
{
	if (dynamic_cast<CWeapon*>(src_obj))	return	t >= 0.0f && t <= 1.0f;
	else return	t >= 0.0f && t <= 1.0f && obj->IsDirectionColliable(nx, ny) == 1;
}
