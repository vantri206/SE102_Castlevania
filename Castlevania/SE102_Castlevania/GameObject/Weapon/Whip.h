#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Ghoul.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "debug.h"
#include "Collision.h"
#include "Weapon.h"
#include <unordered_set>

#define WHIP_STATE_LV1 0
#define WHIP_STATE_LV2 1
#define WHIP_STATE_LV3 2

#define ANI_ID_WHIP_LV1 0
#define ANI_ID_WHIP_LV2 1
#define ANI_ID_WHIP_LV3 2

struct WhipOffset
{
    int whipoffsetX, whipoffsetY;
};

struct WhipFrameSize
{
    int frameWidth, frameHeight;
};

const WhipFrameSize whipFrameSize[3][3] =			//x is level (1, 2, 3), y is frame index
{

    { { 8, 24 }, { 16, 20 }, { 24, 8 } },

    { { 8, 24 }, { 16, 20 }, { 24, 6 } },

    { { 8, 22 }, { 16, 20 }, { 40, 6 } },
};

const WhipOffset whipOffset[3][2][3] =			//x is level (1, 2, 3), y is simon state (0: standing, 1: sitting), z is frame index
{
    {
        { {17, 3}, {10, 2}, {-24, -4} },              

        { {17, 7}, {10, 1}, {-24, -1} }
    },

    {
        { {17, 3}, {10, 2}, {-24, -4} },

        { {17, 7}, {10, 1}, {-24, -1} }
    },

    {
        { {17, 3}, {10, 2}, {-32, -4} },

        { {17, 7}, {10, 1}, {-32, -1} }
    }
};

class CWhip : public CWeapon
{
protected:
    int level;
	CSimon* owner;
	std::unordered_set<CEnemy*> enemiesTarget;
public:
	CWhip(CSimon*);

	void Update(DWORD dt, vector<CGameObject*>* coObjects);
	void UpdateSize(int currentFrameIndex);
	void UpdatePostition(int currentFrameIndex);

	void OnNoCollision(DWORD dt) {}
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void Render();

    void SetWhipLevel(int level);

	void SetState(int state) {}

	int IsCollidable();

    void ResetAnimation();

	void SetOwner(CSimon* simon) { this->owner = simon; }
	CSimon* GetOwner() { return this->owner; }
};