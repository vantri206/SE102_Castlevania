#include "SimonSit.h"
#include "SimonIdle.h"
#include "Simon.h"
#include "SimonSitAttack.h"

CSimonSit::CSimonSit(CSimon* simon) : CSimonState(simon)
{
	simon->SetPhysical(0.0f, 0.0f, 0.0f, SIMON_GRAVITY);
	simon->SetAniId(ID_ANI_SIMON_SIT);
	simon->SetSize(SIMON_SIT_WIDTH, SIMON_SIT_HEIGHT);
}

void CSimonSit::KeyDownHandle(int keyCode)
{
	if (keyCode == DIK_A)
	{
		if (simon->CanUseSubWeapon())
			simon->SetState(new CSimonSitAttack(simon, SUB_WEAPON));
		else simon->SetState(new CSimonSitAttack(simon, PRIMARY_WEAPON));
	}
	else if (keyCode == DIK_RIGHT) {
		simon->SetDirectionX(1);
	}
	else if (keyCode == DIK_LEFT) {
		simon->SetDirectionX(-1);
	}
}
void CSimonSit::KeyUpHandle(int keyCode)
{
    if (keyCode == DIK_DOWN)
    {
		simon->SetPosition(simon->GetX(), simon->GetY() + (SIMON_IDLE_HEIGHT - SIMON_SIT_HEIGHT) / 2);
		simon->SetState(new CSimonIdle(simon));
    }

}
void CSimonSit::Update(DWORD dt)
{
	float vx, vy;
	simon->GetSpeed(vx, vy);
	if (vy < 0.0f)
	{
		simon->SetPosition(simon->GetX(), simon->GetY() + (SIMON_FALLING_HEIGHT - SIMON_SIT_HEIGHT) / 2);
		simon->SetState(new CSimonFalling(simon));
	}
}

void CSimonSit::OnNoCollision(DWORD dt)
{
	
}

void CSimonSit::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		simon->OnCollisionWithEnemy(enemy);
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
