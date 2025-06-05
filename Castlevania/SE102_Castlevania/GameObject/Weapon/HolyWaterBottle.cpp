#pragma once
#include "HolyWaterBottle.h"
#include "Animation.h"
#include "Enemy.h"
#include "BreakableObject.h"
#include "Brick.h"

CHolyWaterBottle::CHolyWaterBottle(float x, float y, int directionX)
{
	this->SetSize(HOLYWATER_BOTTLE_WIDTH, HOLYWATER_BOTTLE_HEIGHT);
	this->SetPosition(x, y);
	burnCooldown = HOLYWATER_BURN_COOLDOWN;
	burnDuration = HOLYWATER_BURN_DURATION;
	nx = directionX;
	vx = HOLYWATER_BOTTLE_SPEED * nx;
	vy = HOLYWATER_BOTTLE_THROW_VY;
	ay = DEFAULT_GRAVITY;
	heartCost = 1;
	damage = 1;

	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(HOLYWATER_ANI_SET_ID));
	this->SetState(HOLYWATER_THROW_STATE);
}

void CHolyWaterBottle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted) return;
	vy += ay * dt;
	x += vx * dt;
	y += vy * dt;	
	if ((!isInViewport()) || (isBreaking() && GetTickCount64() - burnStartTime >= burnDuration))
	{
		this->Destroy();
		return;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CHolyWaterBottle::Render()
{
	animation_set->at(ani_id)->Render(x, y, nx, width, height);
}

void CHolyWaterBottle::SetState(int state)
{
	switch (state)
	{
	case HOLYWATER_THROW_STATE:
		this->ani_id = ANI_ID_HOLYWATER_THROW;
		break;
	case HOLYWATER_BREAKING_STATE:
		this->ani_id = ANI_ID_HOLYWATER_BREAKING;
		break;
	}
	this->state = state;
}

void CHolyWaterBottle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking())
	{
		this->HolyWaterBreak();
	}
	if (!isBreaking()) return;
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		if (enemy)
		{
			DWORD currentTime = GetTickCount64();
			if (enemiesTarget.find(enemy) == enemiesTarget.end() || currentTime - enemiesTarget[enemy] >= burnCooldown)
			{
				enemy->TakenDamage(this->damage);
				enemiesTarget[enemy] = currentTime;
			}
		}
	}
	else if (dynamic_cast<CBreakableObject*>(e->obj))
	{
		CBreakableObject* breakableObj = dynamic_cast<CBreakableObject*>(e->obj);
		if (breakableObj) breakableObj->OnHit();
	}
}

int CHolyWaterBottle::IsCollidable()
{
	return (!isDeleted);
}

void CHolyWaterBottle::HolyWaterBreak()
{
	if (isBreaking()) return;
	this->SetSpeed(0.0f, 0.0f);
	ay = 0.0f;
	burnStartTime = GetTickCount64();
	this->SetState(HOLYWATER_BREAKING_STATE);
	this->SetSize(HOLYWATER_BURN_WIDTH, HOLYWATER_BURN_HEIGHT);
}

int CHolyWaterBottle::isBreaking()
{
	return(this->state == HOLYWATER_BREAKING_STATE);
}

void CHolyWaterBottle::Destroy()
{
	this->Delete();
}