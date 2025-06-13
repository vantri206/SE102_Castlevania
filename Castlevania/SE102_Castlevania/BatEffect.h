#pragma once

#include "Effect.h"
#include "GameDefine.h"
#include "Animations.h"
#include "debug.h"
#include "Game.h"

#define MENUBAT_EFFECT_WIDTH 72
#define MENUBAT_EFFECT_HEIGHT 56

#define MENUBAT_EFFECT_DURATION 4000

#define ID_ANI_MENUBAT_START 0
#define ID_ANI_MENUBAT_LOOP 1

class CMenuBatEffect : public CGameEffect
{
protected:
    int ani_id;
public:
    CMenuBatEffect(float x, float y)
    {
        this->animation_set = CAnimationSets::GetInstance()->Get(MENUBAT_ANI_SET_ID);
        int ani_id = ID_ANI_MENUBAT_START;
        width = MENUBAT_EFFECT_WIDTH;
        height = MENUBAT_EFFECT_HEIGHT;

        this->x = x;
        this->y = y;
        this->startTime = GetTickCount64();
        this->effectDuration = MENUBAT_EFFECT_DURATION;
    }

    void Update(DWORD dt) override
    {
        if (ani_id != ID_ANI_MENUBAT_LOOP && GetTickCount64() - startTime >= effectDuration)
        {
            ani_id = ID_ANI_MENUBAT_LOOP;
        }
    } 

    void Render()
    {
        animation_set->at(ani_id)->Render(x, y, POSITIVE_DIRECTION, width, height);
    }
};
