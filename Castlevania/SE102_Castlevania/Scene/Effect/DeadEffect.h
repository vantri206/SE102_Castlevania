#pragma once

#include "Effect.h"
#include "GameDefine.h"
#include "Animations.h"
#include "Game.h"

#define DEAD_EFFECT_STATE 0

#define DEAD_EFFECT_WIDTH 8
#define DEAD_EFFECT_HEIGHT 14

class CDeadEffect : public CGameEffect
{
protected:
    CAnimationSet animations;
    LPANIMATION_SET animation_set;
public:
    CDeadEffect(float x, float y, DWORD duration) : CGameEffect(x, y, duration)
    {
        this->animation_set = CAnimationSets::GetInstance()->Get(DEADEFFECT_ANI_SET_ID);
        width = DEAD_EFFECT_WIDTH;
        height = DEAD_EFFECT_HEIGHT;
    }

    void Update(DWORD dt) 
    {
        CGameEffect::Update(dt);
        CAnimation* ani = animation_set->at(DEAD_EFFECT_STATE); 
        int frameIndex = ani->GetCurrentFrameIndex();
    }

    void Render() 
    {
        animation_set->at(DEAD_EFFECT_STATE)->Render(x, y, POSITIVE_DIRECTION, width, height);
    }
};
