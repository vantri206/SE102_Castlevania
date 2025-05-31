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

#define SIMON_IDLE_WIDTH 16
#define SIMON_IDLE_HEIGHT 30

CSimonIdle::CSimonIdle(CSimon* simon)
{
    simon->SetAniId(ID_ANI_SIMON_IDLE);
    simon->SetAccel(0.0f, GRAVITY);
    simon->SetSpeed(0.0f, 0.0f);
    simon->SetSize(SIMON_IDLE_WIDTH, SIMON_IDLE_HEIGHT);
    simon->SetOnStair(false);
}
void CSimonIdle::KeyUpHandle(CSimon* simon, int keyCode)
{
	//DebugOut(L"Keycode: %d\n", keyCode);

}

void CSimonIdle::KeyDownHandle(CSimon* simon, int keyCode)
{
	//DebugOut(L"Keycode: %d\n", keyCode);
    if (keyCode == DIK_RIGHT)
    {
        simon->SetDirectionX(1);
        simon->SetState(new CSimonWalking(simon));
    }
    else if (keyCode == DIK_LEFT) {
        simon->SetDirectionX(-1);
        simon->SetState(new CSimonWalking(simon));
    }
    else if (keyCode == DIK_D)
    {
        simon->SetState(new CSimonJump(simon));
    }
    else if (keyCode == DIK_S) 
    {
        simon->SetPosition(simon->GetX(), simon->GetY() - 3.0f);
        simon->SetState(new CSimonSit(simon));
    }
    else if (keyCode == DIK_A) 
    {
        simon->SetState(new CSimonAttack(simon));
    }
    if (keyCode == DIK_UP && simon->IsNearStairUp())
    {
		CStair* stair = simon->GetNearbyStair();
        if (stair != nullptr)
        {
            float stairX = stair->GetX();
			int stairDirection = stair->GetHorizontalDirection();
            simon->SetState(new CSimonAutoWalking(simon,stairX,stairDirection,true));
        }
    }
    else if (keyCode == DIK_DOWN && simon->IsNearStairDown())
    {
        CStair* stair = simon->GetNearbyStair();
        if (stair != nullptr)
        {
            float stairX = stair->GetX();
            int stairDirection = stair->GetHorizontalDirection();
            simon->SetState(new CSimonAutoWalking(simon, stairX, stairDirection,false));
        }
    }
} 

void CSimonIdle::Update(CSimon* simon, DWORD dt)
{

}

void CSimonIdle::OnNoCollision(CSimon* simon, DWORD dt)
{
    
}


void CSimonIdle::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
	{
        CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
        simon->OnCollisionWithEnemy(enemy);
	}
	else if (e->ny != 0 && e->obj->IsBlocking())
	{
		simon->SetVy(0.0f);
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
        simon->SetVx(0.0f);
	}
}
