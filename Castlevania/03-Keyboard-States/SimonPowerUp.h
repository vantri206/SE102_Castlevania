#pragma once

#include "SimonState.h"

#define SIMON_POWERUP_TIME 900

class CSimonPowerUp : public CSimonState
{
protected:
    DWORD startPowerUp = 0;
public:
    CSimonPowerUp(CSimon* simon);
    void KeyDownHandle(int keyCode) {}
    void KeyUpHandle(int keyCode) {}
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt) {}
    void OnCollisionWith(LPCOLLISIONEVENT e);
};