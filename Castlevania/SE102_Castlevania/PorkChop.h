#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "Item.h"
#include "GameSetting.h"

#define ID_ANI_PORKCHOP 0

class CPorkChop : public CItem
{
protected:
    int healValue;
public:
    CPorkChop();
    int getHealthValue();
};
