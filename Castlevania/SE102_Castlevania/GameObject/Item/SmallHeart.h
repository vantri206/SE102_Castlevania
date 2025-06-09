#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "Item.h"

#define SMALL_HEART_WIDTH 8
#define SMALL_HEART_HEIGHT 8

#define ID_ANI_SMALLHEART 0

#define SMALLHEART_HEART_VALUE 1

#define SMALLHEART_SWING_TIME 200

#define HEART_GRAVITY -0.0075f
#define HEART_MAX_FALLSPEED -0.01f

#define SMALLHEART_SWING_SPEED 0.75f

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
