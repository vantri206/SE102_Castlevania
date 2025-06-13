#pragma once

#include "Effect.h"
#include "GameDefine.h"
#include "Animations.h"
#include "Game.h"

#define SPLASH_EFFECT_WIDTH 8
#define SPLASH_EFFECT_HEIGHT 16

#define ANI_ID_SPLASH_EFFECT 0

class CSplashEffect : public CGameEffect
{
protected:
    float ay;
    float vx, vy;
public:
    CSplashEffect(float x, float y, float vx, float vy, float ay)
    {
        this->animation_set = CAnimationSets::GetInstance()->Get(SPLASHEFFECT_ANI_SET_ID);
        this->width = SPLASH_EFFECT_WIDTH;
        this->height = SPLASH_EFFECT_HEIGHT;

        this->x = x;
        this->y = y;
        this->vx = vx;
        this->vy = vy;
        this->ay = ay;
    }

    void Update(DWORD dt)
    {
        vy += ay * dt;

        x += vx * dt;
        y += vy * dt;

        CGameEffect::Update(dt);
    }

    void Render()
    {
        animation_set->at(ANI_ID_SPLASH_EFFECT)->Render(x, y, POSITIVE_DIRECTION, width, height);
    }
};
