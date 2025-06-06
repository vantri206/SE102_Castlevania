#pragma once
#include "SimonState.h"

class CSimonHurt : public CSimonState
{
protected:
    DWORD startHurtTime;
public:
    CSimonHurt(CSimon* simon);
    void KeyDownHandle(CSimon* simon, int keyCode);
    void KeyUpHandle(CSimon* simon, int keyCode);
    void Update(CSimon* simon, DWORD dt);
    void OnNoCollision(CSimon* simon, DWORD dt);
    void OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e);
};
