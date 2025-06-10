#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "Item.h"
#include "GameSetting.h"

#define ID_ANI_BIGHEART 0

class CBigHeart : public CItem
{
protected:
    int heartValue;
public:
    CBigHeart();
    int getHeartValue();
};
