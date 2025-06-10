#pragma once

#include "GameDefine.h"
#include "GameObject.h"
#include "debug.h"
#include <Camera.h>

class CGameEffect 
{
protected:
    float x, y;
    float width, height;
    DWORD startTime, effectDuration;
    bool isFinished;
    CAnimationSet animations;
    LPANIMATION_SET animation_set;
public:
    CGameEffect() {}
    virtual ~CGameEffect() {}

    virtual void Update(DWORD dt)
    {
        RECT cam = CCamera::GetInstance()->GetCamRect();
        if(!(this->x >= cam.left && this->x <= cam.right && this->y >= cam.bottom && this->y <= cam.top))
        {
            isFinished = true;
        }
    }
    virtual void Render() = 0;

    bool IsFinished() { return isFinished; }
};

