#include "SimonJump.h"
#include "SimonIdle.h"
#include "debug.h"
#include "Game.h"
#include "Simon.h"
#include "SimonFalling.h"

CSimonJump::CSimonJump(CSimon* simon)
{
	jumpStartTime = GetTickCount64();
	simon->SetVy(SIMON_JUMP_SPEED);
	simon->SetAy(0.0f);
	simon->SetAniId(ID_ANI_SIMON_JUMP);
}
void CSimonJump::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonJump::KeyUpHandle(CSimon* simon, int keyCode)
{
    if ((keyCode == DIK_RIGHT && simon->GetDirectionX() > 0) || (keyCode == DIK_LEFT && simon->GetDirectionX() < 0))
    {
        simon->SetAx(0.0f);
        simon->SetVx(0.0f);
    }
    
}
void CSimonJump::Update(CSimon* simon, DWORD dt) 
{
	if (GetTickCount64() - jumpStartTime > JUMP_DURATION)
	{
		simon->SetState(new CSimonFalling(simon));
	}
}

void CSimonJump::OnNoCollision(CSimon* simon, DWORD dt)
{
	simon->UpdateMoving(dt);
}

void CSimonJump::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		simon->SetState(new CSimonHurt(simon));
	}
	else if (e->ny > 0 && e->obj->IsBlocking())
	{
		simon->SetState(new CSimonIdle(simon));
	}
	else if (e->ny < 0 && e->obj->IsBlocking())
	{
		simon->SetState(new CSimonFalling(simon));
	}
}

