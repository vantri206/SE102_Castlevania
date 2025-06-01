#include "SimonJump.h"
#include "SimonIdle.h"
#include "debug.h"
#include "Game.h"
#include "Simon.h"
#include "SimonFalling.h"
#include "SimonHurt.h"

CSimonJump::CSimonJump(CSimon* simon) : CSimonState(simon)
{
	jumpStartTime = GetTickCount64();
	float vx, vy, ax, ay;
	simon->GetPhysical(vx, vy, ax, ay);
	simon->SetPhysical(vx, SIMON_JUMP_SPEED, ax, GRAVITY);
	simon->SetAniId(ID_ANI_SIMON_JUMP);
}
void CSimonJump::KeyDownHandle(int keyCode) {}
void CSimonJump::KeyUpHandle(int keyCode)
{
    if ((keyCode == DIK_RIGHT && simon->GetDirectionX() > 0) || (keyCode == DIK_LEFT && simon->GetDirectionX() < 0))
    {
        simon->SetAx(0.0f);
        simon->SetVx(0.0f);
    }
    
}
void CSimonJump::Update(DWORD dt) 
{
	float x, y;
	simon->GetSpeed(x, y);
	if(y < 0)
		simon->SetState(new CSimonFalling(simon));
}

void CSimonJump::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}

void CSimonJump::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		simon->OnCollisionWithEnemy(enemy);
	}
}

