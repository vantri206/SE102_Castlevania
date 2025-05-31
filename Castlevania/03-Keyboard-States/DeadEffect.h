#pragma once

#include "Effect.h"
#include "GameDefine.h"
#include "Animations.h"
#include "Game.h"

#define DEAD_EFFECT_STATE 0

const int deadeffectFrameWidths[] = { 2, 3, 4 };
const int deadeffectFrameHeights[] = { 7, 6, 8 };

class CDeadEffect : public CGameEffect
{
protected:
    CAnimationSet animations;
    LPANIMATION_SET animation_set;
public:
    CDeadEffect(float x, float y, DWORD duration) : CGameEffect(x, y, duration)
    {
        this->animation_set = CAnimationSets::GetInstance()->Get(DEADEFFECT_ANI_SET_ID);
        width = deadeffectFrameWidths[0];
        height = deadeffectFrameHeights[0];
    }

    void Update(DWORD dt) 
    {
        CGameEffect::Update(dt);
        CAnimation* ani = animation_set->at(DEAD_EFFECT_STATE); 
        int frameIndex = ani->GetCurrentFrameIndex();
        UpdateSize(frameIndex);
    }

    void Render() 
    {
        animation_set->at(DEAD_EFFECT_STATE)->Render(x, y, POSITIVE_DIRECTION, width, height);
    }

    void UpdateSize(int frameIndex)
    {
        if (frameIndex >= 0 && frameIndex < 3)
        {
            width = deadeffectFrameWidths[frameIndex];
            height = deadeffectFrameHeights[frameIndex];
        }
    }
};
