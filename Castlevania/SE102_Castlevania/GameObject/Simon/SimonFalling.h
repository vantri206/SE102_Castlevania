#pragma once
#include "SimonState.h"

class CSimonFalling : public CSimonState
{
public:
    CSimonFalling(CSimon* simon);
    void KeyDownHandle(int keyCode);
    void KeyUpHandle(int keyCode);
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
};
