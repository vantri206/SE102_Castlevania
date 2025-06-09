#pragma once

#include "Effect.h"
#include "GameDefine.h"
#include "Animations.h"
#include "Game.h"

#define BRICK_EFFECT_WIDTH 10
#define BRICK_FRAGMENT_HEIGHT 10

#define BRICKBREAK_EFFECT_ANI 0

class CBrickFragment : public CGameEffect
{
protected:
    float ay;
    float vx, vy;
public:
    CBrickFragment(float x, float y, float vx, float ay)
    {
        this->animation_set = CAnimationSets::GetInstance()->Get(BREAKBRICKEFFECT_ANI_SET_ID);
        this->width = BRICK_EFFECT_WIDTH;
        this->height = BRICK_FRAGMENT_HEIGHT;
        
        this->x = x;
        this->y = y;
        this->vx = vx;
        this->ay = ay;
        this->vy = 0;
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
        animation_set->at(BRICKBREAK_EFFECT_ANI)->Render(x, y, POSITIVE_DIRECTION, width, height);
    }
};
