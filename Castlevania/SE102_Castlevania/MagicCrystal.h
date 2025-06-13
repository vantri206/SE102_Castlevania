#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "Item.h"
#include "GameSetting.h"

#define ID_ANI_DOUBLESHOT 0
#define ID_ANI_MAGICCRYSTAL 0

class CMagicCrystal : public CItem
{
protected: 
    float ay;
public:
    CMagicCrystal();
};
