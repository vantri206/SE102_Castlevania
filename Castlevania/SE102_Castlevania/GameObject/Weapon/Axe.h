#pragma once
#include "Weapon.h"
#include "GameDefine.h"
#include "Enemy.h"
#include <unordered_set>

#define AXE_SPEED 0.1075f
#define AXE_THROW_VY 0.4f
#define AXE_WIDTH 15
#define AXE_HEIGHT 14

#define AXE_STATE_THROW 0

#define AXE_ANI_ID_THROW 0

class CAxe : public CWeapon
{
protected:
    float ay;
    std::unordered_set<CEnemy*> enemiesTarget;
public:
    CAxe(float x, float y, int directionX);

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void OnCollisionWith(LPCOLLISIONEVENT e);
    int IsCollidable();
    void Destroy();
    int GetHeartCost() { return heartCost; }
};
