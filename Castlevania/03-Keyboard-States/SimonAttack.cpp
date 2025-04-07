#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
void CSimonAttack::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonAttack::KeyUpHandle(CSimon* simon, int keyCode) {}
void CSimonAttack::Update(CSimon* simon) {
    simon->SetAniId(ID_ANI_SIMON_ATTACK);
    if (GetTickCount() - attackStartTime > 300) {
        simon->SetState(new CSimonIdle());
    }
}
