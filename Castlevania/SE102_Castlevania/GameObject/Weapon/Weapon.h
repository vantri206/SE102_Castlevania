#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#include "GameDefine.h"

class CWeapon : public CGameObject
{
protected:
	CSimon* owner;
	int damage;
	int heartCost;
public:
	CWeapon()
	{
		vx = vy = 0;
		x = y = 0;
		width = height = 0;
		nx = 1;
		owner = nullptr;
		damage = 0;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void Render() = 0;

	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual int IsOverlappable() { return 1; }

	virtual int CanCollisionWithObj(LPGAMEOBJECT objDests);
	virtual int isInViewport();

	void SetOwner(CSimon* simon) { this->owner = simon; }
	CSimon* GetOwner() { return this->owner; }

	virtual void SetWeaponDamage(int dmg) { this->damage = dmg; }
	virtual int GetCurrentDamage() { return this->damage; }

	virtual int GetHeartCost() { return 0; }
};