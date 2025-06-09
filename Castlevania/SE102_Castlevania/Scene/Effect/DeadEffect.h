#pragma once

#include "Effect.h"
#include "GameDefine.h"
#include "Animations.h"
#include "debug.h"
#include "Game.h"

#define DEAD_EFFECT_ANI 0

#define DEAD_EFFECT_WIDTH 8
#define DEAD_EFFECT_HEIGHT 14

class CDeadEffect : public CGameEffect
{
public:
    CDeadEffect(float x, float y, DWORD duration)
    {
        this->animation_set = CAnimationSets::GetInstance()->Get(DEADEFFECT_ANI_SET_ID);
        width = DEAD_EFFECT_WIDTH;
        height = DEAD_EFFECT_HEIGHT;

        this->x = x;
        this->y = y;
        startTime = GetTickCount64();
        this->effectDuration = duration;
        this->isFinished = false;
    }

    void Update(DWORD dt) 
    {
        if (!isFinished && GetTickCount64() - startTime >= effectDuration)
            isFinished = true;
        CGameEffect::Update(dt);
    }

    void Render() 
    {
        animation_set->at(DEAD_EFFECT_ANI)->Render(x, y, POSITIVE_DIRECTION, width, height);
    }
};
