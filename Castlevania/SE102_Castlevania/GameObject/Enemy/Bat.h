#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "debug.h"

#define BAT_STATE_FLYING 0
#define BAT_STATE_DEAD 1

#define ANI_ID_BAT_FLYING 0

class CBat : public CEnemy
{
protected:
	DWORD lastSwingTime;
public:
	CBat();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable();

	void SetState(int state);

	void LoadExtraSetting(vector<int> extra_settings);

	int CheckEnemyCanActive(CSimon* simon);

	void ActiveEnemy();

	int isDead();
};