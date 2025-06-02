#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#include "GameDefine.h"

#define ENEMY_DEAD_TIME 900

class CEnemy : public CGameObject
{
protected:
	float ax, ay;
	int health, attack;
	bool isActive;
	DWORD startDeathTime;

public:
	CEnemy()
	{
		ax = 0;
		ay = GRAVITY;
		startDeathTime = 0;
		health = attack = 0;
		isActive = false;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void Render() = 0;

	virtual void SetPhysical(float vx, float vy, float ax, float ay);

	void GetBoundingBox(float& l, float& t, float& r, float& b);
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
	virtual void TriggerNormalEffect(int duration);

	virtual int isActived(){ return isActive; }
	virtual void ActiveEnemy() { isActive = 1; }
};