
#include "Simon.h"
#include "SimonIdle.h"
#include "SimonState.h"
#include "SimonHurt.h"

void CSimonHurt::KeyUpHandle(CSimon* simon, int keyCode) { }
void CSimonHurt::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonHurt::Update(CSimon* simon) {
    simon->SetAniId(ID_ANI_SIMON_HURT); 
    if (GetTickCount64() - startHurtTime > SIMON_HURT_TIME)
    {
        finishedHurt = true;
    }
    if (finishedHurt && simon->IsOnPlatform()) 
    {
        simon->SetState (new CSimonIdle());
    }
}