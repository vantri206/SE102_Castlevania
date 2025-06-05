#pragma once

#include "MorningStar.h"

CMorningStar::CMorningStar()
{

	this->SetSize(MORNINGSTAR_WIDTH, MORNINGSTAR_HEIGHT);
	vx = vy = 0.0f;
	ay = DEFAULT_GRAVITY;

	LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(MORNINGSTAR_ANI_SET_ID);
	this->SetAnimationSet(ani_set);
	this->SetState(MORNINGSTAR_STATE_NORMAL);
}

void CMorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMorningStar::Render()
{
	animation_set->at(ID_ANI_MORNINGSTAR)->Render(x, y, nx, width, height);
}

void CMorningStar::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CMorningStar::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny > 0 && e->obj->IsBlocking())
	{
		vy = 0.0f;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0.0f;
	}
}

void CMorningStar::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 4;
	t = y + height / 2;
	r = x + width / 4;
	b = y - height / 2;
}
