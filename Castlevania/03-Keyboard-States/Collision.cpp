#include "Collision.h"
#include "GameObject.h"
#include "Debug.h"

#define BLOCK_PUSH_FACTOR 0.01f

CCollision* CCollision::__instance = NULL;

int CCollisionEvent::WasCollided() {
	return
		t >= 0 && t <= 1.0f && obj->IsDirectionColliable(nx, ny) == 1;
}

CCollision* CCollision::GetInstance()
{
	if (__instance == NULL) __instance = new CCollision();
	return __instance;
}

void CCollision::SweptAABB(
	float ml, float mt, float mr, float mb,	//moving box
	float dx,
	float dy,
	float sl, float st, float sr, float sb, //static box
	float& t, float& nx, float& ny)
{
	float dx_entry, dy_entry, tx_entry, ty_entry;
	float dx_exit, dy_exit, tx_exit, ty_exit;
	float t_entry, t_exit;
	t = -1.0f, nx = 0.0f, ny = 0.0f; //no collision

	//Broad-Pharsing
	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;
	if (bl > sr || br < sl || bt > sb || bb < st)
		return; //no collision

	if (dx == 0 && dy == 0)  return; //no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}
	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}
	if (dx == 0) {
		tx_entry = -std::numeric_limits<float>::infinity();
		tx_exit = std::numeric_limits<float>::infinity();
	}
	else {
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}
	if (dy == 0) {
		ty_entry = -std::numeric_limits<float>::infinity();
		ty_exit = std::numeric_limits<float>::infinity();
	}
	else {
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}

	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit || t_entry < 0.0f)
		return; //no collision

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
LPCOLLISIONEVENT CCollision::SweptAABB(
	LPGAMEOBJECT objSrc,
	DWORD dt,
	LPGAMEOBJECT objDest)
{
	float ml, mt, mr, mb;	//moving box
	float sl, st, sr, sb;	//static box
	float t, nx, ny;

	float mvx, mvy, svx, svy;
	objSrc->GetSpeed(mvx, mvy);
	objDest->GetSpeed(svx, svy);

	float mdx = mvx * dt;
	float mdy = mvy * dt;
	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = mdx - sdx;
	float dy = mdy - sdy;

	objSrc->GetBoundingBox(ml, mt, mr, mb);
	objDest->GetBoundingBox(sl, st, sr, sb);
	SweptAABB(ml, mt, mr, mb, dx, dy, sl, st, sr, sb, t, nx, ny);
	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, dx, dy, objDest, objSrc);
	return e;
}
void CCollision::Scan(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* objDests, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < objDests->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABB(objSrc, dt, objDests->at(i));

		if (e->WasCollided() == 1)
			coEvents.push_back(e);
		else
			delete e;
	}
}
void CCollision::Filter(
	LPGAMEOBJECT objSrc,
	vector<LPCOLLISIONEVENT>& coEvents,
	LPCOLLISIONEVENT& colX,
	LPCOLLISIONEVENT& colY,
	int filterBlock = 1,
	int filterX = 1,
	int filterY = 1) {
	float min_tx = 1.0f;
	float min_ty = 1.0f;
	float min_ix = -1;
	float min_iy = -1;
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (e->isDeleted) continue;
		if (e->obj->IsDeleted) continue;
		if (filterBlock == 1 && e->obj->IsBlocking() == 0) continue;
		if (e->t < min_tx && e->nx != 0 && filterX == 1)
		{
			min_tx = e->t;
			min_ix = i;
		}
		if (e->t < min_ty && e->ny != 0 && filterY == 1)
		{
			min_ty = e->t;
			min_iy = i;
		}
		if (min_tx > 0)
			colX = coEvents[min_ix];
		if (min_ty > 0)
			colY = coEvents[min_iy];
	}
}
void CCollision::Process(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vector<LPCOLLISIONEVENT> coEvents;
	LPCOLLISIONEVENT colX = NULL;
	LPCOLLISIONEVENT colY = NULL;
	coEvents.clear();

	if (objSrc->IsCollidable() == 0) {
		Scan(objSrc, dt, coObjects, coEvents);
	}
	if (coObjects->size() == 0) {
		objSrc->OnNoCollision(dt);
	}
	else {
		Filter(objSrc, coEvents, colX, colY);
		float x, y, vx, vy, dx, dy;
		objSrc->GetPosition(x, y);
		objSrc->GetSpeed(vx, vy);
		dx = vx * dt;
		dy = vy * dt;
		if (colX != NULL && colY != NULL) {
			if (colY->t < colX->t) //collision on Y ?
			{
				y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
				objSrc->SetPosition(x, y);
				objSrc->OnCollisionWith(colY);
				LPCOLLISIONEVENT colX_other = NULL; //biến mới để lưu va chạm X sau khi kiểm tra lại

				colX->isDeleted = true; //Xóa va chạm cũ đã không còn đúng sau khi va chạm Y

				coEvents.push_back(SweptAABB(objSrc, dt, colX->obj));

				Filter(objSrc, coEvents, colX_other, colY, 1, 1, 0); //lọc va chạm mới theo X
				if (colX_other != NULL) {  //xử lí va chạm X
					x += colX_other->t * dx + colX_other->nx * BLOCK_PUSH_FACTOR;
					objSrc->SetPosition(x, y);
				}
				else x += dx;
			}
			else //collision on X ?
			{
				x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;

				objSrc->SetPosition(x, y);
				objSrc->OnCollisionWith(colX);

				LPCOLLISIONEVENT colY_other = NULL; //biến mới để lưu va chạm Y sau khi kiểm tra lại

				colY->isDeleted = true; //Xóa va chạm cũ đã không còn đúng sau khi va chạm X

				coEvents.push_back(SweptAABB(objSrc, dt, colY->obj));
				Filter(objSrc, coEvents, colX, colY, 1, 0, 1); //lọc va chạm mới theo Y

				if (colY != NULL) {  //xử lí va chạm Y
					y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
					objSrc->SetPosition(x, y);
				}
				else y += dy;
			}
		}
		else if (colX != NULL) //collision on X ?
		{
			x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
			y += dy;
			objSrc->OnCollisionWith(colX);
		}
		else if (colY != NULL) //collision on Y ?
		{
			x += dx;
			y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
			objSrc->OnCollisionWith(colY);
		}
		else {
			x += dx;
			y += dy;
			objSrc->SetPosition(x, y);
		}
		//
		// Scan all non-blocking collisions for further collision logic
		//
		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (e->isDeleted) continue;
			if (e->obj->IsBlocking()) continue;  // blocking collisions were handled already, skip them
			if (e->src_obj->IsDeleted) continue; // source object is deleted
			objSrc->OnCollisionWith(e);
		}
		for (UINT i = 0; i < coEvents.size(); i++)
		{
			delete coEvents[i];
		}
	}
}