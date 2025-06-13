#pragma once

#include "MoneyBag.h"
#include <debug.h>

CMoneyBag::CMoneyBag()
{
	this->SetSize(MONEYBAG_WIDTH, MONEYBAG_HEIGHT);
	ay = DEFAULT_GRAVITY;
	score = 0;

	startSpawn = -1;
	
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(MONEYBAG_ANI_SET_ID));
	state = MONEYBAG_STATE_IDLE;
}

void CMoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (IsDeleted()) return;
	if (isSpawning() && GetTickCount64() - startSpawn >= MONEYBAG_SPAWN_DURATION) FinishedSpawning();
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMoneyBag::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CMoneyBag::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
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
		this->score = extra_settings[0];
	this->SetMoneyBagAni();
}

void CMoneyBag::SetMoneyBagAni()
{
	switch (this->score)
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
		this->ani_id = ID_ANI_MONEYBAG_400;
	}
}

void CMoneyBag::StartSpawning()
{
	ay = 0.0f;
	vy = 0.02f;
	startSpawn = GetTickCount64();
	state = MONEYBAG_STATE_SPAWN;
}

void CMoneyBag::FinishedSpawning()
{
	ay = DEFAULT_GRAVITY;
	vy = 0.0f;
	state = MONEYBAG_STATE_IDLE;
}

int CMoneyBag::GetScore()
{
	return score;
}