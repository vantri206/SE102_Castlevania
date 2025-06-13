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
	damage = NORMAL_ENEMY_ATTACK;
	isDeleted = false;

	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(FIREBALL_ANI_SET_ID));
}
CFireball::CFireball(float x, float y, float targetX, float targetY)
{
    this->SetSize(FIREBALL_HEIGHT, FIREBALL_HEIGHT);
    this->SetPosition(x, y);

    // Tính hướng bay dựa trên vector từ (x, y) đến (targetX, targetY)
    float dx = targetX - x;
    float dy = targetY - y;
    float length = sqrt(dx * dx + dy * dy);

    // Đảm bảo không chia cho 0
    if (length != 0)
    {
        vx = FIREBALL_SPEED * dx / length;
        vy = FIREBALL_SPEED * dy / length;
    }
    else
    {
        vx = FIREBALL_SPEED;
        vy = 0;
    }

    nx = (vx > 0) ? 1 : -1;
    damage = 1;
    isDeleted = false;

    this->SetAnimationSet(CAnimationSets::GetInstance()->Get(FIREBALL_ANI_SET_ID));
}

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted) return;
	x += vx * dt;
	y += vy * dt;
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