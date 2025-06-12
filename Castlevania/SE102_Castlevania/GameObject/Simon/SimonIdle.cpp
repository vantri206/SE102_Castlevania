#pragma once

#include "Simon.h"

#include "SimonIdle.h"
#include "SimonWalking.h"
#include "SimonJump.h"
#include "SimonAttack.h"
#include "SimonSit.h"
#include "Enemy.h"
#include "SimonHurt.h"
#include "Stair.h"
#include "SimonStairUpIdle.h"
#include "SimonStairDownIdle.h"
#include "SimonAutoWalking.h"
#include "Item.h"
#include "MorningStar.h"
#include "SimonPowerUp.h"
#include "SimonDie.h"
#include <TriggerZone.h>
#include <Fireball.h>

CSimonIdle::CSimonIdle(CSimon* simon) : CSimonState(simon)
{
    simon->SetAniId(ID_ANI_SIMON_IDLE);
    simon->SetPhysical(0.0f, 0.0f, 0.0f, SIMON_GRAVITY);
    simon->SetSize(SIMON_IDLE_WIDTH, SIMON_IDLE_HEIGHT);
}
void CSimonIdle::KeyUpHandle(int keyCode)
{
	//DebugOut(L"Keycode: %d\n", keyCode);

}

void CSimonIdle::KeyDownHandle(int keyCode)
{
	//DebugOut(L"Keycode: %d\n", keyCode);
    if (keyCode == DIK_RIGHT)
    {
        simon->SetDirectionX(1);
        simon->SetState(new CSimonWalking(simon));
    }
    else if (keyCode == DIK_LEFT) 
    {
        simon->SetDirectionX(-1);
        simon->SetState(new CSimonWalking(simon));
    }
    else if (keyCode == DIK_S)
    {
        simon->SetState(new CSimonJump(simon));
    }
    else if (keyCode == DIK_A) 
    {
        if (CGame::GetInstance()->IsKeyDown(DIK_UP))
        {
            if(simon->CanUseSubWeapon())
                simon->SetState(new CSimonAttack(simon, SUB_WEAPON));
        }
        else simon->SetState(new CSimonAttack(simon, PRIMARY_WEAPON));
    }
    else if (keyCode == DIK_UP && simon->IsNearStairUp())
    {
		CStair* stair = simon->GetNearbyStair();
        if (stair != nullptr)
        {
            float stairX, stairY;
            int stairDirection;
            stair->GetPosition(stairX, stairY);
            stairDirection = stair->GetHorizontalDirection();
            simon->SetState(new CSimonAutoWalking(simon, stairX, stairY, stairDirection, SIMON_STATE_WALKING_UP));
        }
    }
    else if (keyCode == DIK_DOWN && simon->IsNearStairDown())
    {

        CStair* stair = simon->GetNearbyStair();
        if (stair != nullptr)
        {
            float stairX, stairY;
            int stairDirection;
            stair->GetPosition(stairX, stairY);
            stairDirection = stair->GetHorizontalDirection();
            simon->SetState(new CSimonAutoWalking(simon, stairX, stairY, stairDirection, SIMON_STATE_WALKING_DOWN));
        }
    }
    else if (keyCode == DIK_DOWN)
    {
        simon->SetPosition(simon->GetX(), simon->GetY() - 4.0f);
        simon->SetState(new CSimonSit(simon));
    }
    else if (keyCode == DIK_G) {
		simon->SetState(new CSimonDie(simon));
    }

} 

void CSimonIdle::Update(DWORD dt)
{
    float vx, vy;
    simon->GetSpeed(vx, vy);
    if (vy < 0)
    {
        simon->SetPosition(simon->GetX(), simon->GetY() - 4.0f);
        simon->SetState(new CSimonFalling(simon));
    }
}

void CSimonIdle::OnNoCollision(DWORD dt)
{
    simon->UpdateMoving(dt);
}


void CSimonIdle::OnCollisionWith(LPCOLLISIONEVENT e)
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
    else if (dynamic_cast<CFireball*>(e->obj))
    {
        CFireball* fireball = dynamic_cast<CFireball*>(e->obj);
        simon->OnCollisionWithBullet(fireball);
    }
    else if (dynamic_cast<CTriggerZone*>(e->obj))
    {
        CTriggerZone* triggerzone = dynamic_cast<CTriggerZone*>(e->obj);
        triggerzone->Trigger();
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
