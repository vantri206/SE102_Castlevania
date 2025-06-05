#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "Dagger.h"
#include "Axe.h"

#define ANI_ID_BIGHEART 0
#define BIGHEART_HEART_VALUE 5

#define HOLYWATERBOTTLE_ITEM_WIDTH 16
#define HOLYWATERBOTTLE_ITEM_HEIGHT 16

#define ID_ANI_ITEM_DAGGER 0
#define ID_ANI_ITEM_AXE 1
#define ID_ANI_ITEM_HOLYWATER 2

class CSubWeaponItem : public CGameObject
{
protected:
    int subWeaponType;
    float ay;
public:
    CSubWeaponItem();

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

    void Render();

    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

    void SetWeaponItem();

    virtual int IsBlocking() { return 0; }
    virtual int IsOverlappable() { return 1; }
    virtual int IsCollidable() { return 1; };

    void OnNoCollision(DWORD dt);

    void OnCollisionWith(LPCOLLISIONEVENT e);

    void LoadExtraSetting(vector<int> extra_settings);
};
