#pragma once

#include "Simon.h"

#include "SimonIdle.h"
#include "Enemy.h"
#include "SimonWalkingStairUp.h"
#include "SimonWalkingStairDown.h"
#include "SimonStairDownIdle.h"

#define SIMON_STAIR_DOWN_WIDTH 16
#define SIMON_STAIR_DOWN_HEIGHT 30

CSimonStairDownIdle::CSimonStairDownIdle(CSimon* simon)
{
    simon->SetAniId(ID_ANI_SIMON_DOWN_IDLE);
    simon->SetAccel(0.0f, 0.0f);
    simon->SetSpeed(0.0f, 0.0f);
    simon->SetSize(SIMON_STAIR_DOWN_WIDTH, SIMON_STAIR_DOWN_HEIGHT);
    simon->SetOnStair(true);
}
void CSimonStairDownIdle::KeyUpHandle(CSimon* simon, int keyCode)
{
    //DebugOut(L"Keycode: %d\n", keyCode);

}

void CSimonStairDownIdle::KeyDownHandle(CSimon* simon, int keyCode)
{
    //DebugOut(L"Keycode: %d\n", keyCode);
    if (keyCode == DIK_UP)
    {
		int simondir = simon->GetDirectionX();
		simon->SetDirectionX(-simondir);
        simon->SetState(new CSimonWalkingStairUp(simon));
    }
    else if (keyCode == DIK_DOWN)
    {
        simon->SetState(new CSimonWalkingStairDown(simon));
    }
    else if (keyCode == DIK_A)
    {
       //simon->SetState(new CSimonAttack(simon));
    }
}

void CSimonStairDownIdle::Update(CSimon* simon, DWORD dt)
{

}

void CSimonStairDownIdle::OnNoCollision(CSimon* simon, DWORD dt)
{

}

void CSimonStairDownIdle::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
    {
        //simon->SetState(new CSimonHurt());
    }
}
