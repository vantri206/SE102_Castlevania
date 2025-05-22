#pragma once
#include <Windows.h>
#include "Collision.h"

class CSimon;

class CSimonState
{
public:
    virtual void KeyUpHandle(CSimon* simon, int keyCode) = 0;
    virtual void KeyDownHandle(CSimon* simon, int keyCode) = 0;
    virtual void Update(CSimon* simon, DWORD dt) = 0;
    virtual void OnNoCollision(CSimon* simon, DWORD dt) = 0;
    virtual void OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e) = 0;
    virtual void Render() {}
    virtual ~CSimonState() {};
};