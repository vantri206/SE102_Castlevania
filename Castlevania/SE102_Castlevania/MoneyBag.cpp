#pragma once

#include "MoneyBag.h"

CMoneyBag::CMoneyBag()
{
	this->SetSize(MONEYBAG_WIDTH, MONEYBAG_HEIGHT);
	vx = vy = 0.0f;
	ay = 0;
	vy = 0.02f;
	hidden = 0;

	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(MONEYBAG_ANI_SET_ID));
}

void CMoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMoneyBag::Render()
{
	animation_set->at(ani_id)->Render(x, y, nx, width, height);
}

void CMoneyBag::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CMoneyBag::OnCollisionWith(LPCOLLISIONEVENT e)
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

void CMoneyBag::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 4;
	t = y + height / 2;
	r = x + width / 4;
	b = y - height / 2;
}

void CMoneyBag::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->point = extra_settings[0];
	this->SetMoneyBagAni();
}

void CMoneyBag::SetMoneyBagAni()
{
	switch (this->point)
	{
	case 400:
		this->ani_id = ID_ANI_MONEYBAG_400;
		break;
	case 700:
		this->ani_id = ID_ANI_MONEYBAG_700;
		break;
	case 1000:
		this->ani_id = ID_ANI_MONEYBAG_1000;
		break;
	default:
		this->ani_id = ID_ANI_MONEYBAG_1000;
	}
}

void CMoneyBag::StartAppearing()
{
	ay = 0;
	vy = 0.1f;
}
