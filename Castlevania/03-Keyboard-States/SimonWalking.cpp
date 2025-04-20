#pragma once

#include "Simon.h"

#include "SimonIdle.h"
#include "SimonWalking.h"
#include "SimonJump.h"
void CSimonWalking::KeyUpHandle(CSimon* simon, int keyCode)
{
	if (keyCode == DIK_RIGHT && simon->GetDirectionX() > 0)
	{
		simon->SetState(new CSimonIdle());
		simon->SetSpeed(0, 0);
	}
	else if (keyCode == DIK_LEFT && simon->GetDirectionX() < 0)
	{
		simon->SetSpeed(0, 0);
		simon->SetState(new CSimonIdle());
	}
}

void CSimonWalking::KeyDownHandle(CSimon* simon, int keyCode)
{
	
}

void CSimonWalking::Update(CSimon* simon)
{
	simon->SetSpeed(SIMON_WALKING_SPEED * simon->GetDirectionX(), 0);
	simon->SetAniId(ID_ANI_SIMON_WALK);
}