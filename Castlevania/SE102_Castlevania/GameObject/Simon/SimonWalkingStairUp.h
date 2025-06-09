#pragma once

#include "SimonState.h"

#define SIMON_TIME_FIRST_STEP_ONSTAIR 20

class CSimonWalkingStairUp : public CSimonState
{
public:
    CSimonWalkingStairUp(CSimon* simon, int isFirstEntry = 0);
    void KeyDownHandle(int keyCode);
    void KeyUpHandle(int keyCode);
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
};