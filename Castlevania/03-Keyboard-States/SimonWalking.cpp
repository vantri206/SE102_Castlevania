﻿#pragma once

#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
#include "SimonWalking.h"
#include "SimonJump.h"
#include "Brick.h"
#include "Enemy.h"
#include "TriggerZone.h"
#include "Debug.h"
#include "SimonHurt.h"
#include "Candle.h"
#include "Game.h"

#define SIMON_WALKING_WIDTH 15
#define SIMON_WALKING_HEIGHT 30

CSimonWalking::CSimonWalking(CSimon* simon)
{
	simon->SetMaxVx(SIMON_WALKING_SPEED * simon->GetDirectionX());
	simon->SetAccel(SIMON_ACCEL_WALK_X * simon->GetDirectionX(), GRAVITY);
	simon->SetAniId(ID_ANI_SIMON_WALK);
	simon->SetSize(SIMON_WALKING_WIDTH, SIMON_WALKING_HEIGHT);
}

void CSimonWalking::KeyUpHandle(CSimon* simon, int keyCode)
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

void CSimonWalking::KeyDownHandle(CSimon* simon, int keyCode)
{
	if (keyCode == DIK_D)
	{
		simon->SetState(new CSimonJump(simon));
	}
	if (keyCode == DIK_A)
	{
		simon->SetState(new CSimonIdle(simon));
		simon->SetState(new CSimonAttack(simon));
	}
}

void CSimonWalking::Update(CSimon* simon, DWORD dt)
{
	float x, y;
	simon->GetSpeed(x, y);
	if (y < 0) simon->SetState(new CSimonFalling(simon));
}
void CSimonWalking::OnNoCollision(CSimon* simon, DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonWalking::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
    {
        CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
        simon->OnCollisionWithEnemy(enemy);
    }
    else if (dynamic_cast<CTriggerZone*>(e->obj))
    {
		CCandle* candle = new CCandle();
		candle->SetPosition(50, 30);
		candle->SetTargetY(40);
		candle->StartAppearing();
		CGame* game = CGame::GetInstance();
		game->GetCurrentScene()->AddObject(candle);
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