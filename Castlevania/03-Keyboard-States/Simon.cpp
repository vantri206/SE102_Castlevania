#pragma once
#include <algorithm>
#include "Simon.h"
#include "Camera.h"
#include "Enemy.h"
#include "Brick.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	currentState->Update(this);

	int mapwidth = CGame::GetInstance()->GetCurrentMapWidth();
	int mapheight = CGame::GetInstance()->GetCurrentMapHeight();

	vx += ax * dt;
	vy += ay * dt;
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	if (GetTickCount64() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (x <= 0 || x >= mapwidth - SIMON_WIDTH)
	{
		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= mapwidth - SIMON_WIDTH)
		{
			x = (float)(mapwidth - SIMON_WIDTH);
		}
	}
	CCamera::GetInstance()->Update(dt, this, mapwidth, mapheight);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CSimon::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}
void CSimon::OnCollisionWith(LPCOLLISIONEVENT e) {
	if(dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if(dynamic_cast<CEnemy*>(e->obj))
		OnCollisionWithEnemy(e);
}
void CSimon::OnCollisionWithBrick(LPCOLLISIONEVENT e) {
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}
}
void CSimon::OnCollisionWithEnemy(LPCOLLISIONEVENT e) {
	if (untouchable == 0)
	{
		SetState(new CSimonHurt());
		StartUntouchable();

		if (x < e->obj->GetX())
			vx = -SIMON_HURT_VX; 
		else
			vx = SIMON_HURT_VX; 

		vy = SIMON_HURT_VY; 
	}
}
void CSimon::OnKeyDown(int keyCode)
{
	currentState->KeyDownHandle(this, keyCode);
}

void CSimon::OnKeyUp(int keyCode)
{
	currentState->KeyUpHandle(this, keyCode);
}

void CSimon::SetState(CSimonState* state) 
{
	currentState.reset(state);
}

CSimonState* CSimon::GetState()
{
	return currentState.get();
}

void CSimon::Render()
{
	animation_set->at(ani_id)->Render(x, y, nx, SIMON_SIZE);
}
