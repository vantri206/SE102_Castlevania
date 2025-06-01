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

#define GHOUL_WALKING_SPEED	0.15f

#define WHIP_STATE_ATTACK 0

#define ANI_ID_WHIP_ATTACK 0

const int whipFrameWidths[] = { 8.5, 16, 22.5 };
const int whipFrameHeights[] = { 24, 19, 8 };


class CWhip : public CWeapon
{
protected:
	CSimon* owner;
	std::unordered_set<CEnemy*> enemiesTarget;
	bool damageCalculator;
public:
	CWhip(CSimon*);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void UpdateSize(int currentFrameIndex);
	void UpdatePostition(int currentFrameIndex);

	void OnNoCollision(DWORD dt) {}
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void Render();

	void SetState(int state) {}
	int IsCollidable();
	int IsBlocking() { return 0; }
	int IsOverlappable() { return 1;}
	void SetOwner(CSimon* simon) { this->owner = simon; }
	CSimon* GetOwner() { return this->owner; }
};