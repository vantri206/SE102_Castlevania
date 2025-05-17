#include <algorithm>
#include "debug.h"
#include "Ghoul.h"
#include "Whip.h"
#include <cstdlib>

void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDead) return;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGhoul::Render()
{
	if (isDead) return;
	animation_set->at(ANI_ID_GHOUL_IDLE)->Render(x, y);
	//RenderBoundingBox();
}

void CGhoul::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDead)
	{
		left = top = right = bottom = 0;
		return;
	}
	left = x - GHOUL_BBOX_WIDTH/2;
	top = y - GHOUL_BBOX_HEIGHT/2;
	right = left + GHOUL_BBOX_WIDTH;
	bottom = top + GHOUL_BBOX_HEIGHT;
}

void CGhoul::OnNoCollision(DWORD dt)
{
	if (isDead) return;
	x += vx * dt;
	y += vy * dt;
}

void CGhoul::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (isDead) return;

	if (dynamic_cast<CGhoul*>(e->obj)) return;
	if (dynamic_cast<CWhip*>(e->obj))
	{
		SetState(GHOUL_STATE_DIE);
		return;
	}
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0.0f;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}
}

void CGhoul::SetState(int state)
{
	switch (state)
	{
	case GHOUL_STATE_DIE:
		vx = 0;
		vy = 0;
		isDead = true;
		DebugOut(L"[INFO] Ghoul died\n");
		break;
	}
}

void CGhoul::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->SetDirection(extra_settings[0]);
}
