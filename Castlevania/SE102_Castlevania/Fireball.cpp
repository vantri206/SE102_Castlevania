#pragma once
#include "Fireball.h"
#include "Animation.h"
#include "Simon.h"

CFireball::CFireball(float x, float y, int directionX)
{
	this->SetSize(FIREBALL_HEIGHT, FIREBALL_HEIGHT);
	this->SetPosition(x, y);
	nx = directionX;
	vx = FIREBALL_SPEED * nx;
	vy = 0;
	damage = 1;
	isDeleted = false;

	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(FIREBALL_ANI_SET_ID));
}

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted) return;
	x += vx * dt;
	if (!this->isInSceneViewport())
	{
		this->Delete();
		return;
	}
}

void CFireball::Render()
{
	animation_set->at(ANI_ID_FIREBALL_NORMAL)->Render(x, y, nx, width, height);
}