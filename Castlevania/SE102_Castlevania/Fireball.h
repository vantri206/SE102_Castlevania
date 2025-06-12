#pragma once
#include "GameSetting.h"
#include "Enemy.h"
#include "GameDefine.h"

#define ANI_ID_FIREBALL_NORMAL 0

class CFireball : public CGameObject
{
protected:
    int damage;
public:
    CFireball(float x, float y, int directionX);

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void OnCollisionWith(LPCOLLISIONEVENT e) {}
    void SetState(int state) {}
};
