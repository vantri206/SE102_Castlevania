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

#define GHOUL_WALKING_SPEED	0.15f

#define WHIP_STATE_ATTACK 0

#define ANI_ID_WHIP_ATTACK 0

const int whipFrameWidths[] = { 8.5, 16, 22.5 };
const int whipFrameHeights[] = { 24, 19, 8 };


class CWhip : public CWeapon
{
protected:

public:
	CWhip();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	CSimon* owner;
public:
	CWhip();

	void Update(DWORD dt);
	void UpdateSize(int currentFrameIndex);
	void UpdatePostition(int currentFrameIndex);

	void OnNoCollision(DWORD dt) {}
	void OnCollisionWith(LPCOLLISIONEVENT e) {}

	void Render();

	void SetState(int state) {}
	int IsCollidable();
	int IsBlocking() { return 0; }
	void SetOwner(CSimon* simon) { this->owner = simon; }
	CSimon* GetOwner() { return this->owner; }
};