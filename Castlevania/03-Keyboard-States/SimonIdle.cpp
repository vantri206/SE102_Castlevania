#pragma once

#include "Simon.h"

#include "SimonIdle.h"
#include "SimonWalking.h"

void CSimonIdle::KeyUpHandle(CSimon* simon, int keyCode)
{
	DebugOut(L"Keycode: %d\n", keyCode);

}


void CSimonIdle::KeyDownHandle(CSimon* simon, int keyCode)
{
	DebugOut(L"Keycode: %d\n", keyCode);
	if (keyCode == DIK_RIGHT)
	{
		simon->SetDirectionX(1);
		simon->SetState(new CSimonWalking());
	}
	else if (keyCode == DIK_LEFT)
	{
		simon->SetDirectionX(-1);
		simon->SetState(new CSimonWalking());
	}
} 

void CSimonIdle::Update(CSimon* simon)
{
	simon->SetSpeed(0, 0);
	simon->SetAniId(ID_ANI_SIMON_IDLE);
}