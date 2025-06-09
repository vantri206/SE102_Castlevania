#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "Item.h"

#define BIG_HEART_WIDTH 12
#define BIG_HEART_HEIGHT 10

#define ID_ANI_BIGHEART 0

#define BIGHEART_HEART_VALUE 5

#define HEART_GRAVITY -0.0075f
#define HEART_MAX_FALLSPEED -0.01f

class CBigHeart : public CItem
{
protected:
    int heartValue;
public:
    CBigHeart();
    int getHeartValue();
};
