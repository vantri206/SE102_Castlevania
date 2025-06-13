#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Animation.h"
#include "Animations.h"
#include "GameSetting.h"
#include "GameDefine.h"
#include "debug.h"
#include "Fireball.h"



#define ANI_ID_PHANTOMBAT_SLEEPING 0
#define ANI_ID_PHANTOMBAT_FLYING 1

#define PHANTOMBAT_STATE_SLEEPING 0
#define PHANTOMBAT_STATE_HOVERING 1
#define PHANTOMBAT_STATE_FLYING 2
#define PHANTOMBAT_STATE_PATROL 3
#define PHANTOMBAT_STATE_ATTACK 4
#define PHANTOMBAT_STATE_DEAD 5

struct BatPointGroup {
	D3DXVECTOR2 left;
	D3DXVECTOR2 middle;
	D3DXVECTOR2 right;
};
struct NearestInPointGroupsInfo {
    D3DXVECTOR2 point;
    int groupIndex;
    std::string pointType; // "left", "middle", "right"
};

class CPhantomBat : public CEnemy
{
protected:
    int state;
	bool isFlying = false;
	bool isattacked = false;
    vector<BatPointGroup> pointGroups;
    vector< D3DXVECTOR2> backPoints;
	int directionpoint = 1; // 1 for left, -1 for 
    int patrolcount = 0;
	DWORD hovering_start = 0;
    D3DXVECTOR2 currentTarget;
    D3DXVECTOR2 attackTarget;
	int currentbackPointIndex = 0;
    int currentGroupIndex = -1;
    float flySpeed = 0.1f;
    float attackSpeed = 0.2f;

public:
    CPhantomBat();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    void SetState(int state);
    void LoadExtraSetting(vector<int> extra_settings);
    int isDead();

	void SetAttackTarget(D3DXVECTOR2 target) { attackTarget = target; }

    void CreateFireball();

    void FlyTo(D3DXVECTOR2 target);
    bool ReachedTarget();
    bool ReachedTarget(D3DXVECTOR2 target);
    D3DXVECTOR2 GetRandomNonMiddlePoint();
    D3DXVECTOR2 GetAboveMiddlePoint();
    D3DXVECTOR2 GetNearestAboveNonMiddlePoint();
    NearestInPointGroupsInfo FindNearestPointInfoInGroups(D3DXVECTOR2 from);
    int FindNearestPointIndex(const D3DXVECTOR2& from, const std::vector<D3DXVECTOR2>& points);

    bool SimonInAttackZone();
};