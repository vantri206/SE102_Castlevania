#pragma once

#include "SimonState.h"

class CSimonIntro : public CSimonState
{
public:
    CSimonIntro(CSimon* simon);
    void KeyDownHandle(int keyCode);
    void KeyUpHandle(int keyCode);
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
};