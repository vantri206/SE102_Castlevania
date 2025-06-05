#pragma once
#include "SimonState.h"

class CSimonHurt : public CSimonState
{
protected:
    DWORD startHurtTime;
public:
    CSimonHurt(CSimon* simon);
    void KeyDownHandle(int keyCode);
    void KeyUpHandle(int keyCode);
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
};
