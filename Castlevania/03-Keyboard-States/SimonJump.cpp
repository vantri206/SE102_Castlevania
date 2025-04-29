#include "SimonJump.h"
#include "SimonIdle.h"
#include "debug.h"
#include "Game.h"
#include "Simon.h"
CSimonJump::CSimonJump()
{
    vy = SIMON_JUMP_SPEED; 
    DWORD jumpStartTime = GetTickCount();
    jumping = true;
}
void CSimonJump::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonJump::KeyUpHandle(CSimon* simon, int keyCode)
{
	if (keyCode == DIK_S)
	{
		simon->SetState(new CSimonIdle());
	}
    if ((keyCode == DIK_RIGHT && simon->GetDirectionX() > 0) || (keyCode == DIK_LEFT && simon->GetDirectionX() < 0))
    {
        simon->SetAx(0.0f);
        simon->SetVx(0.0f);
    }
    
}
void CSimonJump::Update(CSimon* simon) 
{
    simon->SetVy(vy);
    simon->SetAniId(ID_ANI_SIMON_JUMP);
	if (GetTickCount() - jumpStartTime > JUMP_DURATION)
	{
		simon->SetState(new CSimonIdle());
	}
}

