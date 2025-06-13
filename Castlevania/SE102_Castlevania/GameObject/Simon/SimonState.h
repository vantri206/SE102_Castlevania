#pragma once
#include <Windows.h>
#include "Collision.h"

class CSimon;

class CSimonState
{
protected:
    CSimon* simon;

public:

    CSimonState(CSimon* simon)
    {
        this->simon = simon;
    }
    virtual ~CSimonState() {}

    virtual void KeyUpHandle(int keyCode) {}
    virtual void KeyDownHandle(int keyCode) {}

    virtual void Update(DWORD dt) = 0;
    virtual void OnNoCollision(DWORD dt) {}
    virtual void OnCollisionWith(LPCOLLISIONEVENT e) {}

    virtual void Render() {}

    virtual bool IsAutoWalking() { return false; }
};
