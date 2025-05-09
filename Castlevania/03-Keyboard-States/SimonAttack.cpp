#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
#include "Whip.h"
CSimonAttack::CSimonAttack(CSimon* simon)
{
    attackStartTime = GetTickCount64();
    simon->SetAniId(ID_ANI_SIMON_ATTACK);
}
void CSimonAttack::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonAttack::KeyUpHandle(CSimon* simon, int keyCode) {}
void CSimonAttack::Update(CSimon* simon, DWORD dt)
{
    if (GetTickCount64() - attackStartTime > 300)
    {
        simon->SetState(new CSimonIdle(simon));
    }
}

void CSimonAttack::OnNoCollision(CSimon* simon, DWORD dt)
{
}

void CSimonAttack::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
}
