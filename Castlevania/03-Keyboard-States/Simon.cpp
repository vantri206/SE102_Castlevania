#pragma once
#include <algorithm>
#include "debug.h"
#include "PlayScene.h"
#include "Simon.h"
#include "Camera.h"
#include "Textures.h"

void CSimon::Update(DWORD dt)
{
	int mapwidth = CGame::GetInstance()->GetCurrentMapWidth();
	int mapheight = CGame::GetInstance()->GetCurrentMapHeight();
	
	x += vx * dt;
	y += vy * dt;
	if (x <= 0 || x >= mapwidth - SIMON_WIDTH) {
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
}
void CSimon::Render()
{
	animation_set->at(ani_id)->Render(x, y, nx, SIMON_SIZE);
}

void CSimon::SetState(int state)
{
	switch (state)
	{
		case SIMON_STATE_IDLE:
		{
			this->SimonIdle();
			ani_id = ID_ANI_SIMON_IDLE;
			break;
		}
		case SIMON_STATE_WALK:
		{
			this->SimonWalk();
			ani_id = ID_ANI_SIMON_WALK;
			break;
		}
		case SIMON_STATE_ATTACK:
		{
			this->SimonAttack();
			ani_id = ID_ANI_SIMON_ATTACK;
			break;
		}
		case SIMON_STATE_GO_UP:
		{
			this->SimonWalkUp();
			ani_id = ID_ANI_SIMON_GO_UP;
			break;
		}
	}
	CGameObject::SetState(state);
}

int CSimon::GetState()
{
	return this->state;
}

void CSimon::SimonWalkUp()
{
	vx = 0;
	if (ny > 0) vy = SIMON_WALKING_SPEED;
	else vy = -SIMON_WALKING_SPEED;
}

void CSimon::SimonWalk()
{
	vy = 0;
	if (nx > 0) vx = SIMON_WALKING_SPEED;
	else vx = -SIMON_WALKING_SPEED;
}

void CSimon::SimonAttack()
{
	vx = 0;
	vy = 0;
}

void CSimon::SimonIdle()
{
	vx = 0;
	vy = 0;
}

void CSimon::SimonSit()
{
	vx = 0;
	vy = 0;
}
void GetBoundingBox()
{

}
