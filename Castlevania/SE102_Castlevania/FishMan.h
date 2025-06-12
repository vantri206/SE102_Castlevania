#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "debug.h"

#define FISHMAN_STATE_JUMP 0
#define FISHMAN_STATE_WALK 1
#define FISHMAN_STATE_ATTACK 2
#define FISHMAN_STATE_DEAD 3

#define ANI_ID_FISHMAN_JUMP 0
#define ANI_ID_FISHMAN_WALK 1
#define ANI_ID_FISHMAN_ATTACK 2

class CFishMan : public CEnemy
{
protected:
    DWORD startAttackTime;
    DWORD lastAttackTime;
public:
    CFishMan();

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

    void Render();

    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    int IsCollidable();

    void SetState(int state);

    void LoadExtraSetting(vector<int> extra_settings);

    int CheckEnemyCanActive(CSimon* simon);

    void CreateFireball();

    void ActiveEnemy();

    int isDead();
};
