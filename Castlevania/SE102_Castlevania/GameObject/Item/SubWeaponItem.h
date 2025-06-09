#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "Dagger.h"
#include "Axe.h"
#include "Item.h"

#define HOLYWATERBOTTLE_ITEM_WIDTH 16
#define HOLYWATERBOTTLE_ITEM_HEIGHT 16

#define ID_ANI_ITEM_DAGGER 0
#define ID_ANI_ITEM_AXE 1
#define ID_ANI_ITEM_HOLYWATER 2

class CSubWeaponItem : public CItem
{
protected:
    int subWeaponType;
public:
    CSubWeaponItem();

    void SetWeaponItem();

    void LoadExtraSetting(vector<int> extra_settings);

    int GetSubWeaponType() { return this->subWeaponType; }
};
