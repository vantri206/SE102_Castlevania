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

#pragma region ANIMATION_ID

#define ANI_ID_GHOUL_IDLE 0
#define ANI_ID_GHOUL_WALK 1

#define GRAVITY -0.002f
class CGhoul : public CEnemy
{
protected:
public:
	CGhoul()
	{
		vx = 0.0f;
		vy = GRAVITY;

		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(GHOUL_ANI_SET_ID));
	}
	void Update(DWORD dt) {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state) {}
	void LoadExtraSetting(vector<int> extra_settings);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; };
};