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
#include <Item.h>
#include "SimonDie.h"
#include "TriggerZone.h"
#include "Fireball.h"
#include "SimonIntro.h"
#include <Portal.h>

#define SIMON_INTRO_WIDTH 16
#define SIMON_INTRO_HEIGHT 32

CSimonIntro::CSimonIntro(CSimon* simon) : CSimonState(simon)
{
    simon->SetAniId(ID_ANI_SIMON_INTRO);
    simon->SetPhysical(0.0f, 0.0f, 0.0f, SIMON_GRAVITY);
    simon->SetSize(SIMON_INTRO_WIDTH, SIMON_INTRO_HEIGHT);
}
void CSimonIntro::KeyUpHandle(int keyCode)
{

}

void CSimonIntro::KeyDownHandle(int keyCode)
{

}

void CSimonIntro::Update(DWORD dt)
{
    float vx, vy;
    simon->GetSpeed(vx, vy);
    if (vy < 0)
    {
        simon->SetState(new CSimonFalling(simon));
    }
}

void CSimonIntro::OnNoCollision(DWORD dt)
{
    simon->UpdateMoving(dt);
}


void CSimonIntro::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CPortal*>(e->obj))
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