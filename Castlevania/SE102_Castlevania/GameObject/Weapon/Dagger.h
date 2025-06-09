#pragma once
#include "Weapon.h"
#include "GameDefine.h"

#define DAGGER_SPEED 0.1f
#define DAGGER_WIDTH 16
#define DAGGER_HEIGHT 10

#define DAGGER_STATE_THROW 0

#define DAGGER_ANI_ID_THROW 0

class CDagger : public CWeapon
{
protected:
    int heartCost;
public:
    CDagger(float x, float y, int directionX);

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void OnCollisionWith(LPCOLLISIONEVENT e);
    int IsCollidable();
    void Destroy();
    int GetHeartCost() { return heartCost; }
};
