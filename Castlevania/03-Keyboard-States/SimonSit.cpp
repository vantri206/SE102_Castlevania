#include "SimonSit.h"
#include "SimonIdle.h"
#include "Simon.h"

CSimonSit::CSimonSit(CSimon* simon)
{
    simon->SetAniId(ID_ANI_SIMON_SIT);
}

void CSimonSit::KeyDownHandle(CSimon* simon, int keyCode)
{
}
void CSimonSit::KeyUpHandle(CSimon* simon, int keyCode)
{
    if (keyCode == DIK_DOWN)
    {
        simon->SetState(new CSimonIdle(simon));
    }
}
void CSimonSit::Update(CSimon* simon, DWORD dt)
{

}

void CSimonSit::OnNoCollision(CSimon* simon, DWORD dt)
{
}

void CSimonSit::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
}
