#pragma once

#include "GameDefine.h"
#include "GameObject.h"

class CGameEffect 
{
protected:
    float x, y;
    float width, height;
    DWORD startTime, effectDuration;
    bool isFinished;
public:
    CGameEffect(float x, float y, DWORD duration)
    {
        width = height = 0;
        this->x = x;
        this->y = y;
        startTime = GetTickCount64();
        this->effectDuration = duration;
        this->isFinished = false;
    }
    virtual ~CGameEffect() {}

    virtual void Update(DWORD dt)
    {
        if (!isFinished && GetTickCount64() - startTime >= effectDuration)
            isFinished = true;
    }
    virtual void Render() = 0;

    bool IsFinished() { return isFinished; }
};

