#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "GameSetting.h"
#include "Item.h"

#define SMALL_HEART_WIDTH 8
#define SMALL_HEART_HEIGHT 8

#define ID_ANI_SMALLHEART 0

class CSmallHeart : public CItem
{
protected:
    int heartValue;
    DWORD lastSwingTime;
public:
    CSmallHeart();

    int getHeartValue();

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

    void OnNoCollision(DWORD dt);

    void OnCollisionWith(LPCOLLISIONEVENT e);
};
