#pragma once

#include "Simon.h"

#include "SimonIdle.h"
#include "Enemy.h"
#include "SimonWalkingStairUp.h"
#include "SimonWalkingStairDown.h"
#include "SimonStairUpIdle.h"

#define SIMON_STAIR_UP_WIDTH 16
#define SIMON_STAIR_UP_HEIGHT 30

CSimonStairUpIdle::CSimonStairUpIdle(CSimon* simon)
{
    simon->SetAniId(ID_ANI_SIMON_UP_IDLE);
    simon->SetAccel(0.0f, 0.0f);
    simon->SetSpeed(0.0f, 0.0f);
    simon->SetSize(SIMON_STAIR_UP_WIDTH, SIMON_STAIR_UP_HEIGHT);
    simon->SetOnStair(true);
}
void CSimonStairUpIdle::KeyUpHandle(CSimon* simon, int keyCode)
{
    //DebugOut(L"Keycode: %d\n", keyCode);

}

void CSimonStairUpIdle::KeyDownHandle(CSimon* simon, int keyCode)
{
    //DebugOut(L"Keycode: %d\n", keyCode);
    if (keyCode == DIK_UP)
    {
        simon->SetState(new CSimonWalkingStairUp(simon));
    }
    else if (keyCode == DIK_DOWN)
    {
        int simondir = simon->GetDirectionX();
        simon->SetDirectionX(-simondir);
        simon->SetState(new CSimonWalkingStairDown(simon));
    }
    else if (keyCode == DIK_A)
    {
        //simon->SetState(new CSimonAttack(simon));
    }
}

void CSimonStairUpIdle::Update(CSimon* simon, DWORD dt)
{

}

void CSimonStairUpIdle::OnNoCollision(CSimon* simon, DWORD dt)
{

}

void CSimonStairUpIdle::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
    {
        //simon->SetState(new CSimonHurt());
    }
}
