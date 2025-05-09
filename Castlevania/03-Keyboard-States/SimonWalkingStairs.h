#pragma once

#include "SimonState.h"

class CSimonWalkingStairs : public CSimonState
{
public:
    CSimonWalkingStairs(CSimon* simon);
    void KeyDownHandle(CSimon* simon, int keyCode);
    void KeyUpHandle(CSimon* simon, int keyCode);
    void Update(CSimon* simon, DWORD dt);
    void OnNoCollision(CSimon* simon, DWORD dt);
    void OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e);
};