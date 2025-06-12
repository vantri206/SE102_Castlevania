#pragma once

#include "Simon.h"

#include "SimonIdle.h"
#include "Enemy.h"
#include "SimonWalkingStairUp.h"
#include "SimonWalkingStairDown.h"
#include "SimonStairDownIdle.h"
#include "SimonStairDownAttack.h"

CSimonStairDownIdle::CSimonStairDownIdle(CSimon* simon) : CSimonState(simon)
{
    simon->SetAniId(ID_ANI_SIMON_DOWN_IDLE);
    simon->SetPhysical(0.0f, 0.0f, 0.0f, 0.0f);
    simon->SetSize(SIMON_STAIR_DOWN_WIDTH, SIMON_STAIR_DOWN_HEIGHT);
    simon->SetOnStair(true);
}
void CSimonStairDownIdle::KeyUpHandle(int keyCode)
{
    //DebugOut(L"Keycode: %d\n", keyCode);

}

void CSimonStairDownIdle::KeyDownHandle(int keyCode)
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
		simon->SetState(new CSimonStairDownAttack(simon));
    }
}

void CSimonStairDownIdle::Update(DWORD dt)
{

}

void CSimonStairDownIdle::OnNoCollision(DWORD dt)
{

}

void CSimonStairDownIdle::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
    {
        CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
        simon->OnCollisionWithEnemyOnStair(enemy);
    }
}
