#pragma once
#include "Weapon.h"
#include "Enemy.h"
#include "GameSetting.h"
#include <unordered_set>

#define HOLYWATER_THROW_STATE 0
#define HOLYWATER_BREAKING_STATE 1

#define ANI_ID_HOLYWATER_THROW 0
#define ANI_ID_HOLYWATER_BREAKING 1

class CHolyWaterBottle : public CWeapon
{
protected:
    float ay;
    DWORD burnStartTime, burnDuration, burnCooldown;
    std::unordered_map<CEnemy*, DWORD> enemiesTarget;
public:
    CHolyWaterBottle(float x, float y, int direction);

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();

    void SetState(int state);

    void OnCollisionWith(LPCOLLISIONEVENT e);
    int IsCollidable();

    void Destroy();

    void HolyWaterBreak();
    int isBreaking();
    int GetHeartCost() { return heartCost; }

    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
