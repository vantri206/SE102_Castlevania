#pragma once
#include "Axe.h"
#include "Animation.h"
#include "Enemy.h"
#include "BreakableObject.h"
#include "Brick.h"

CAxe::CAxe(float x, float y, int directionX)
{
	this->SetSize(AXE_WIDTH, AXE_HEIGHT);
	this->SetPosition(x, y);
	nx = directionX;
	vx = AXE_SPEED * nx;
	vy = AXE_THROW_VY;
	ay = GRAVITY;
	heartCost = 1;
	damage = 2;

	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(AXE_ANI_SET_ID));
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted) return;
	vy += ay * dt;
	x += vx * dt;
	y += vy * dt;
	if (!this->isInViewport())
	{
		this->Destroy();
		return;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CAxe::Render()
{
	animation_set->at(AXE_ANI_ID_THROW)->Render(x, y, nx, width, height);
}

void CAxe::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		if (enemy)
		{
			if (enemiesTarget.find(enemy) == enemiesTarget.end())
			{
				enemiesTarget.insert(enemy);
				enemy->TakenDamage(this->damage);
			}
		}
	}
	else if (dynamic_cast<CBreakableObject*>(e->obj))
	{
		CBreakableObject* breakableObj = dynamic_cast<CBreakableObject*>(e->obj);
		if (breakableObj) breakableObj->OnHit();
	}
}

int CAxe::IsCollidable()
{
	return (!isDeleted);
}
void CAxe::Destroy()
{
	this->Delete();
}