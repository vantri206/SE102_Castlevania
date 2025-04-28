#pragma once

#include "Simon.h"

#include "SimonIdle.h"
#include "SimonWalking.h"
#include "SimonJump.h"
void CSimonWalking::KeyUpHandle(CSimon* simon, int keyCode)
{
	if (keyCode == DIK_RIGHT && simon->GetDirectionX() > 0)
	{
		simon->SetAx(0.0f);
		simon->SetVx(0.0f);
		simon->SetState(new CSimonIdle());
	}
	else if (keyCode == DIK_LEFT && simon->GetDirectionX() < 0)
	{
		simon->SetAx(0.0f);
		simon->SetVx(0.0f);
		simon->SetState(new CSimonIdle());
	}
}

void CSimonWalking::KeyDownHandle(CSimon* simon, int keyCode)
{
	
}

void CSimonWalking::Update(CSimon* simon)
{
	simon->SetMaxVx(SIMON_WALKING_SPEED * simon->GetDirectionX());
	simon->SetAx(SIMON_ACCEL_WALK_X*simon->GetDirectionX());
	simon->SetAniId(ID_ANI_SIMON_WALK);
}