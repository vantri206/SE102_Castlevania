#include "SimonDie.h"
#include "Simon.h"

#define SIMON_DIE_WIDTH 30
#define SIMON_DIE_HEIGHT 22
CSimonDie::CSimonDie(CSimon* simon) : CSimonState(simon) 
{
    simon->SetAniId(ID_ANI_SIMON_DIE);
    simon->SetPhysical(0.0f, 0.0f, 0.0f, SIMON_GRAVITY);
    simon->SetSize(SIMON_DIE_WIDTH, SIMON_DIE_HEIGHT);

    startDead = GetTickCount64();
    simon->StartDead();
}

void CSimonDie::Update(DWORD dt)
{
    if (GetTickCount64() - startDead >= SIMON_DEAD_TIME)
    {
        CSceneManager::GetInstance()->RequestReloadToCheckpoint();
    }
}

