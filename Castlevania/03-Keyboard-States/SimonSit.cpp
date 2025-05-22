#include "SimonSit.h"
#include "SimonIdle.h"
#include "Simon.h"

#define SIMON_SIT_WIDTH 16
#define SIMON_SIT_HEIGHT 24

CSimonSit::CSimonSit(CSimon* simon)
{
	simon->SetSpeed(0.0f, 0.0f);
	simon->SetAccel(0.0f, GRAVITY);
	simon->SetAniId(ID_ANI_SIMON_SIT);
	simon->SetSize(SIMON_SIT_WIDTH, SIMON_SIT_HEIGHT);
}

void CSimonSit::KeyDownHandle(CSimon* simon, int keyCode)
{
}
void CSimonSit::KeyUpHandle(CSimon* simon, int keyCode)
{
    if (keyCode == DIK_S)
    {
		simon->SetPosition(simon->GetX(), simon->GetY() + 3.0f);
        simon->SetState(new CSimonIdle(simon));
    }
}
void CSimonSit::Update(CSimon* simon, DWORD dt)
{

}

void CSimonSit::OnNoCollision(CSimon* simon, DWORD dt)
{
	simon->SetState(new CSimonFalling(simon));
}

void CSimonSit::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{

}
