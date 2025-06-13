#pragma once

#include "Effect.h"
#include "GameDefine.h"
#include "Animations.h"
#include "Game.h"

#define POINT_EFFECT_400_SPRITES_ID 90030
#define POINT_EFFECT_700_SPRITES_ID 90031
#define POINT_EFFECT_1000_SPRITES_ID 90032
#define POINT_EFFECT_DURATION 500

class CPointEffect : public CGameEffect
{
protected:
    int score;
public:
    CPointEffect(float x, float y, int score)
    {
        this->x = x;
        this->y = y;
        this->score = score;
        this->startTime = GetTickCount64();
        this->effectDuration = POINT_EFFECT_DURATION;
    }

    void Update(DWORD dt)
    {
        if (GetTickCount64() - startTime >= effectDuration)
        {
            isFinished = true;
        }
    }

    void Render()
    {
        CSprites* sprites = CSprites::GetInstance();
        switch (score)
        {
        case 400:
            sprites->GetInstance()->Get(POINT_EFFECT_400_SPRITES_ID)->Draw(x, y, -1);
            break;
        case 700:
            sprites->GetInstance()->Get(POINT_EFFECT_700_SPRITES_ID)->Draw(x, y, -1);
            break;
        case 1000:
            sprites->GetInstance()->Get(POINT_EFFECT_1000_SPRITES_ID)->Draw(x, y, -1);
            break;
        default: 
            sprites->GetInstance()->Get(POINT_EFFECT_400_SPRITES_ID)->Draw(x, y, -1);
        }
    }
};
