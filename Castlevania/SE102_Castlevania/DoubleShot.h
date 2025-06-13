#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "Item.h"
#include "GameSetting.h"

#define ID_ANI_DOUBLESHOT 0

#define DOUBLESHOT_WIDTH 16
#define DOUBLESHOT_HEIGHT 16

class CDoubleShot : public CItem
{
protected: 
    float ay;
public:
    CDoubleShot();
};
