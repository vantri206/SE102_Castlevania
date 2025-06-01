#include "SimonPowerUp.h"
#include "Simon.h"

#define SIMON_POWERUP_WIDTH 16
#define SIMON_POWERUP_HEIGHT 30

CSimonPowerUp::CSimonPowerUp(CSimon* simon) : CSimonState(simon)
{
	startPowerUp = GetTickCount64();
	simon->StartUntouchable();
	simon->SetAniId(ID_ANI_SIMON_POWER_UP);
	simon->SetPhysical(0.0f, 0.0f, 0.0f, GRAVITY);
	simon->SetSize(SIMON_POWERUP_WIDTH, SIMON_POWERUP_HEIGHT);
}

void CSimonPowerUp::Update(DWORD dt)
{
	if (GetTickCount64() - startPowerUp >= SIMON_POWERUP_TIME)
	{
		simon->FinishedUntouchable();
		simon->SetState(new CSimonIdle(simon));
	}
}

void CSimonPowerUp::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		simon->SetVy(0.0f);
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		simon->SetVx(0.0f);
	}
}
