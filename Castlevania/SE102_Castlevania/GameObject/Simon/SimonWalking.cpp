#pragma once

#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
#include "SimonWalking.h"
#include "SimonJump.h"
#include "SimonPowerUp.h"
#include "Brick.h"
#include "Enemy.h"
#include "Debug.h"
#include "SimonHurt.h"
#include "MorningStar.h"

#define SIMON_WALKING_WIDTH 16
#define SIMON_WALKING_HEIGHT 32

CSimonWalking::CSimonWalking(CSimon* simon) : CSimonState(simon)
{
	simon->SetMaxVx(SIMON_WALKING_SPEED * simon->GetDirectionX());
	simon->SetAccel(SIMON_ACCEL_WALK_X * simon->GetDirectionX(), DEFAULT_GRAVITY);
	simon->SetAniId(ID_ANI_SIMON_WALK);
	simon->SetSize(SIMON_WALKING_WIDTH, SIMON_WALKING_HEIGHT);
}

void CSimonWalking::KeyUpHandle(int keyCode)
{
	if (keyCode == DIK_RIGHT && simon->GetDirectionX() > 0)
	{
		simon->SetState(new CSimonIdle(simon));
	}
	else if (keyCode == DIK_LEFT && simon->GetDirectionX() < 0)
	{
		simon->SetState(new CSimonIdle(simon));
	}
}

void CSimonWalking::KeyDownHandle(int keyCode)
{
	if (keyCode == DIK_D)
	{
		simon->SetState(new CSimonJump(simon));
	}
}

void CSimonWalking::Update(DWORD dt)
{
	float x, y;
	simon->GetSpeed(x, y);
	if (y < 0) simon->SetState(new CSimonFalling(simon));
}
void CSimonWalking::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonWalking::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		simon->OnCollisionWithEnemy(enemy);
	}
	if (dynamic_cast<CMorningStar*>(e->obj))
	{
		simon->SetState(new CSimonPowerUp(simon));
	}
	else if (e->ny > 0 && e->obj->IsBlocking())
	{
		simon->SetVy(0.0f);
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		simon->SetVx(0.0f);
	}
}