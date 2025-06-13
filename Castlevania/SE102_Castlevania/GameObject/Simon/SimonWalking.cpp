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
#include "TriggerZone.h"
#include "Portal.h"

CSimonWalking::CSimonWalking(CSimon* simon) : CSimonState(simon)
{
	simon->SetMaxVx(SIMON_WALKING_SPEED * simon->GetDirectionX());
	simon->SetAccel(SIMON_ACCEL_WALK_X * simon->GetDirectionX(), SIMON_GRAVITY);
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
	if (keyCode == DIK_S)
	{
		simon->SetState(new CSimonJump(simon));
	}

	if (keyCode == DIK_A)
	{
		simon->SetAx(0.0f);
		simon->SetVx(0.0f);
		if (CGame::GetInstance()->IsKeyDown(DIK_UP))
		{
			if (simon->CanUseSubWeapon())
				simon->SetState(new CSimonAttack(simon, SUB_WEAPON));
		}
		else simon->SetState(new CSimonAttack(simon, PRIMARY_WEAPON));
	}
}

void CSimonWalking::Update(DWORD dt)
{
	float vx, vy;
	simon->GetSpeed(vx, vy);
	if (vy < 0)
	{
		simon->SetPosition(simon->GetX(), simon->GetY() - (SIMON_WALKING_HEIGHT - SIMON_FALLING_HEIGHT) / 2);
		simon->SetState(new CSimonFalling(simon));
	}
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
	else if (dynamic_cast<CItem*>(e->obj))
	{
		CItem* item = dynamic_cast<CItem*>(e->obj);
		simon->OnCollisionWithItem(item);
	}
	else if (dynamic_cast<CTriggerZone*>(e->obj))
	{
		CTriggerZone* triggerzone = dynamic_cast<CTriggerZone*>(e->obj);
		triggerzone->Trigger();
	}
	else if (dynamic_cast<CPortal*>(e->obj))
	{
		CPortal* portal = dynamic_cast<CPortal*>(e->obj);
		portal->Active();
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