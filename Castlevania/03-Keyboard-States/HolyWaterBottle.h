#pragma once
#include "Weapon.h"
#include "Enemy.h"
#include <unordered_set>

#define HOLYWATER_BOTTLE_SPEED 0.05f
#define HOLYWATER_BOTTLE_THROW_VY 0.1f

#define HOLYWATER_THROW_STATE 0
#define HOLYWATER_BREAKING_STATE 1

#define ANI_ID_HOLYWATER_THROW 0
#define ANI_ID_HOLYWATER_BREAKING 1

#define HOLYWATER_BOTTLE_WIDTH 8
#define HOLYWATER_BOTTLE_HEIGHT 4
#define HOLYWATER_BURN_WIDTH 16
#define HOLYWATER_BURN_HEIGHT 13

#define HOLYWATER_BURN_DURATION 1600
#define HOLYWATER_BURN_COOLDOWN 400

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
};
