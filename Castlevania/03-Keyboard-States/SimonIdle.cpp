#pragma once

#include "Simon.h"

#include "SimonIdle.h"
#include "SimonWalking.h"
#include "SimonJump.h"
#include "SimonAttack.h"
#include "SimonSit.h"
#include "Enemy.h"

#define SIMON_IDLE_WIDTH 16
#define SIMON_IDLE_HEIGHT 30

CSimonIdle::CSimonIdle(CSimon* simon)
{
    simon->SetAniId(ID_ANI_SIMON_IDLE);
    simon->SetAccel(0.0f, GRAVITY);
    simon->SetSpeed(0.0f, 0.0f);
    simon->SetSize(SIMON_IDLE_WIDTH, SIMON_IDLE_HEIGHT);
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
    else if (keyCode == DIK_S)
    {
        simon->SetState(new CSimonJump(simon));
    }
    else if (keyCode == DIK_DOWN) 
    {
        simon->SetState(new CSimonSit(simon));
    }
    else if (keyCode == DIK_A) 
    {
        simon->SetState(new CSimonAttack(simon));
    }
} 

void CSimonIdle::Update(CSimon* simon, DWORD dt)
{

}

void CSimonIdle::OnNoCollision(CSimon* simon, DWORD dt)
{
    simon->SetState(new CSimonFalling(simon));
}

void CSimonIdle::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
	{
		simon->SetState(new CSimonHurt());
	}
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		simon->SetVy(0.0f);
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
        simon->SetVx(0.0f);
	}
}
