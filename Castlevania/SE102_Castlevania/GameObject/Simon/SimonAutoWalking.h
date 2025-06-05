#pragma once

#include "SimonState.h"

class CSimonAutoWalking : public CSimonState
{
protected:
    float targetX, targetY;
    int nextState;
    int finishedDirection;
public:
    CSimonAutoWalking(CSimon* simon, float x, float y, int direction, int simonState);
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    bool CheckReachedTarget();
    void ChangeState();
    virtual void KeyUpHandle(int keyCode) {}
    virtual void KeyDownHandle(int keyCode) {}
};