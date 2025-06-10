#include "SimonDie.h"
#include "Simon.h"

CSimonDie::CSimonDie(CSimon* simon) : CSimonState(simon) {

    simon->SetAniId(ID_ANI_SIMON_DIE);
    simon->SetPhysical(0.0f, 0.0f, 0.0f, DEFAULT_GRAVITY);
    simon->SetSize(SIMON_DIE_WIDTH, SIMON_DIE_HEIGHT);
}
void CSimonDie::KeyDownHandle(int keyCode){}
void CSimonDie::KeyUpHandle(int keyCode){}
void CSimonDie::Update(DWORD dt){}
void CSimonDie::OnNoCollision(DWORD dt){}
void CSimonDie::OnCollisionWith(LPCOLLISIONEVENT e){}