#include "SimonFloat.h"
#include "Simon.h"
#include "SimonFalling.h"
#include "GameDefine.h"

CSimonFloat::CSimonFloat(CSimon* simon) : CSimonState(simon)
{
	simon->SetSize(SIMON_SIT_WIDTH, SIMON_SIT_HEIGHT);
	simon->SetAniId(ID_ANI_SIMON_SIT);

	floatStart = GetTickCount64();
}

void CSimonFloat::Update(DWORD dt)
{
	if (GetTickCount64() - floatStart >= SIMON_FLOATING_TIME)
	{
		simon->SetPosition(simon->GetX(), simon->GetY() - (SIMON_JUMP_HEIGHT - SIMON_SIT_HEIGHT) / 2);
		simon->SetState(new CSimonFalling(simon));
	}
}

void CSimonFloat::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}
