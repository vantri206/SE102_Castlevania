#pragma once
#include "EFfect.h"

#define FLASH_EFFECT_BLINK_TIME 60

class CFlashEffect : public CGameEffect
{
public:
    CFlashEffect()
    {
        isFinished = false;
        startTime = GetTickCount64();
        width = SCREEN_WIDTH;
        height = SCREEN_HEIGHT;
        effectDuration = FLASH_EFFECT_DURATION;
    }
    void Update(DWORD dt)
    {
        if (!isFinished && GetTickCount64() - startTime >= effectDuration)
            isFinished = true;
    }
    void Render()
    {  
        if (isFinished) return;
        else
        {
            DWORD now = GetTickCount64();
            if ((now / FLASH_EFFECT_BLINK_TIME) % 2 != 0) return;
            float cx, cy;
            cx = CCamera::GetInstance()->GetX();
            cy = CCamera::GetInstance()->GetY();
            CSprites::GetInstance()->Get(99990)->Draw(cx + width / 2, cy + height / 2, 1, width, height);
        }
    }
};
