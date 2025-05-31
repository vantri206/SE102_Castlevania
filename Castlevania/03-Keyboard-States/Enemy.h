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
	int health, attack;

	DWORD startDeathTime;
public:
	CEnemy()
	{
		ax = 0;
		ay = GRAVITY;
		maxVx = maxVy = 0;
		startDeathTime = 0;
		health = attack = 0;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void Render() = 0;

	float GetMaxVx() { return maxVx; }
	float GetMaxVy() { return maxVy; }

	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual int IsOverlappable() { return 1; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e) = 0;

	virtual void SetState(int state) = 0;

	virtual void LoadExtraSetting(vector<int> extra_settings);

	virtual bool isDead() { return false; }

	virtual int GetHealth() { return health; }
	virtual void SetHealth(int hp) { health = hp; }
	virtual int GetAttack() { return attack; }
	virtual void SetAttack(int atk) { attack = atk; }

	virtual void TakenDamage(int damage) { health -= damage; }
	virtual void NormalEnemyDead(int duration);
};