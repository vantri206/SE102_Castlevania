#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "Item.h"
#include "GameSetting.h"

#define ID_ANI_DOUBLESHOT 0
#define ID_ANI_MAGICCRYSTAL 0

#define MAGICCRYSTAL_WIDTH 14
#define MAGICCRYSTAL_HEIGHT 16
class CMagicCrystal : public CItem
{
protected: 
    float ay;
    DWORD startAppearing;
public:
    CMagicCrystal();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
