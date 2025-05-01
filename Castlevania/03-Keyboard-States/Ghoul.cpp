#include <algorithm>
#include "debug.h"
#include "Ghoul.h"
#include <cstdlib>

void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CGhoul::Render()
{
	animation_set->at(ANI_ID_GHOUL_WALK)->Render(x, y);
}

void CGhoul::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CGhoul::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGhoul*>(e->obj)) return;
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0.0f;
	}
	else
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}
}
void CGhoul::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->SetDirection(extra_settings[0]);
}