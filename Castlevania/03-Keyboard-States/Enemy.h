#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#include "GameDefine.h"

#define GRAVITY -0.002f

class CEnemy : public CGameObject
{
protected:

	float maxVx, maxVy;
	float ax, ay;
	int hp, attack;

public:
	CEnemy()
	{
		ax = 0;
		ay = GRAVITY;
		maxVx = maxVy = 0;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void Render() = 0;

	float GetMaxVx() { return maxVx; }
	float GetMaxVy() { return maxVy; }

	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual int IsOverlappable() { return 1; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetState(int state) = 0;

	virtual void LoadExtraSetting(vector<int> extra_settings);
};