#include <algorithm>
#include "debug.h"
#include "Ghoul.h"
#include "Whip.h"
#include <cstdlib>

CGhoul::CGhoul()
{
	vx = vy = 0.0f;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(GHOUL_ANI_SET_ID));
	this->SetState(GHOUL_STATE_IDLE);
	this->SetAniId(ANI_ID_GHOUL_IDLE);
}
void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGhoul::Render()
{
	animation_set->at(this->GetAniId())->Render(x, y, nx, width, height);
}

void CGhoul::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CGhoul::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGhoul*>(e->obj)) return;
	if (dynamic_cast<CWeapon*>(e->obj))
	{
		DebugOut(L"gh vs w\n");
		this->Delete();
	}
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0.0f;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0.0f;
	}
}

void CGhoul::SetState(int state)
{
	switch (state)
	{
	case GHOUL_STATE_IDLE:
		this->SetAniId(ANI_ID_GHOUL_IDLE);
	case GHOUL_STATE_WALK:
		this->SetAniId(ANI_ID_GHOUL_WALK);
	}
	this->state = state;
}

int CGhoul::IsCollidable()
{
	return 1;
}
void CGhoul::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->SetDirectionX(extra_settings[0]);
}
