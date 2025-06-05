#pragma once
#include "Dagger.h"
#include "Animation.h"
#include "Enemy.h"
#include "BreakableObject.h"

CDagger::CDagger(float x, float y, int directionX) 
{
    this->SetSize(DAGGER_WIDTH, DAGGER_HEIGHT);
    this->SetPosition(x, y);
    nx = directionX;
    vx = DAGGER_SPEED * nx;
	heartCost = 1;
	damage = 1;

    this->SetAnimationSet(CAnimationSets::GetInstance()->Get(DAGGER_ANI_SET_ID));
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted) return;
    x += vx * dt;
	if (!this->isInViewport())
	{
		this->Destroy();
		return;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CDagger::Render()
{
    animation_set->at(DAGGER_ANI_ID_THROW)->Render(x, y, nx, width, height);
}

void CDagger::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		if (enemy)	enemy->TakenDamage(this->damage);
		this->Destroy();
	}
	else if (dynamic_cast<CBreakableObject*>(e->obj))
	{
		CBreakableObject* breakableObj = dynamic_cast<CBreakableObject*>(e->obj);
		if (breakableObj) breakableObj->OnHit();
		this->Destroy();
	}
}

int CDagger::IsCollidable()
{
	return (!isDeleted);
}
void CDagger::Destroy()
{
	this->Delete();
}