#pragma once
#include "GameObject.h"
#include "Enemy.h"

#include "Animation.h"
#include "Animations.h"

#include "GameDefine.h"
#include "debug.h"

#define PANTHER_RUN_SPEED 0.25f
#define PANTHER_JUMP_VY 0.15f

#define PANTHER_STATE_IDLE	0
#define PANTHER_STATE_RUN 1
#define PANTHER_STATE_HOVERING 2
#define PANTHER_STATE_DEAD 3

#pragma region ANIMATION_ID

#define ANI_ID_PANTHER_IDLE 0
#define ANI_ID_PANTHER_WALK 1
#define ANI_ID_PANTHER_HOVERING 2

#define PANTHER_RANGE_ACTIVE 150

class CPanther : public CEnemy
{
protected:
public:
	CPanther();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable();

	int CanCollisionWithObj(CGameObject* objDest);

	void SetState(int state);

	void LoadExtraSetting(vector<int> extra_settings);

	int CheckEnemyCanActive(CSimon* simon);

	void ActiveEnemy();

	int isHovering();

	int isDead();
};