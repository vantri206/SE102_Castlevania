#pragma once
#include "SimonState.h"

class CSimonFloat : public CSimonState
{
protected:
    DWORD floatStart;
public:
    CSimonFloat(CSimon* simon);
    void KeyDownHandle(int keyCode);
    void KeyUpHandle(int keyCode);
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
};
