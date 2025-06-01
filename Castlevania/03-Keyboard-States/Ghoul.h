#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "debug.h"

#define GHOUL_WALKING_SPEED	0.15f

#define GHOUL_STATE_IDLE	0
#define GHOUL_STATE_WALK	1
#define GHOUL_STATE_DEAD	2

#define ANI_ID_GHOUL_IDLE 0
#define ANI_ID_GHOUL_WALK 1

#define GHOUL_RANGE_ACTIVE 150.0f

class CGhoul : public CEnemy
{
protected:
public:
	CGhoul();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable();

	void SetState(int state);

	void LoadExtraSetting(vector<int> extra_settings);

	int CheckEnemyCanActive(CSimon* simon);

	void ActiveEnemy();

	bool isDead();
};