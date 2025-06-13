#pragma once
#include "GameObject.h"
#include <memory>

#include "SimonState.h"
#include "SimonIdle.h"
#include "SimonHurt.h"
#include "SimonFalling.h"

#include "Brick.h"
#include "Enemy.h"

#include "debug.h"
#include "GameDefine.h"
#include "GameSetting.h"
#include "Stair.h"

#include "Weapon.h"
#include <Item.h>


#define SIMON_MAX_WHIP_LEVEL 3

#define UNTOUCHABLE 1
#define NOT_UNTOUCHABLE 0

#define SIMON_BLINK_TIME 120

#define SIMON_WALKING_SPEED 0.3f
#define SIMON_ACCEL_WALK_X	0.0005f

#define SIMON_WALKING_STAIR_SPEED 0.075f
#define SIMON_AUTO_WALKING_STAIR_SPEED 0.03f

#define SIMON_HURT_VX 0.1f    
#define SIMON_HURT_VY 0.3f   
#define SIMON_HURT_TIME 500  
#define SIMON_UNTOUCHABLE_TIME 2000 
#define SIMON_INVISIBLE_TIME 4000

#define SIMON_JUMP_SPEED 0.5f

#define SIMON_STATE_IDLE	0
#define SIMON_STATE_WALK	1
#define SIMON_STATE_JUMP	2
#define SIMON_STATE_SIT		3
#define SIMON_STATE_ATTACK	4
#define SIMON_STATE_WALKING_UP	5
#define SIMON_STATE_WALKING_DOWN 6
#define SIMON_STATE_IDLE_UP 7
#define SIMON_STATE_IDLE_DOWN 8
#define SIMON_STATE_INTRO 9
#define SIMON_STATE_SIT_ATTACK 10



#pragma region ANIMATION_ID		//xem thu tu animation trong resource

#define ID_ANI_SIMON_IDLE			0
#define ID_ANI_SIMON_WALK			1
#define ID_ANI_SIMON_JUMP			2
#define ID_ANI_SIMON_SIT			3
#define ID_ANI_SIMON_ATTACK			4
#define ID_ANI_SIMON_UP_IDLE		5
#define ID_ANI_SIMON_DOWN_IDLE		6
#define ID_ANI_SIMON_GO_UP			7
#define ID_ANI_SIMON_GO_DOWN		8
#define ID_ANI_SIMON_ATTACK_DOWN	9
#define ID_ANI_SIMON_ATTACK_UP		10
#define ID_ANI_SIMON_HURT			11
#define ID_ANI_SIMON_DIE			12
#define ID_ANI_SIMON_POWER_UP		13
#define ID_ANI_SIMON_SIT_ATTACK		15

#define SIMON_WIDTH 16
#define SIMON_HEIGHT 32
class CSimon : public CGameObject
{
protected:
	float maxVx;
	float ax, ay;

	unique_ptr<CSimonState> currentState;

	int untouchable;
	ULONGLONG untouchable_start;

	int invisible;
	ULONGLONG invisible_start;

	CStair* nearbyStair;	
	bool isOnStair = false;

	CWeapon* currentWeapon;
	int currentSubWeaponType;
	int subWeaponLimit;
	vector<CWeapon*> activeSubWeaponList;

	bool isAutoWalking;

	int health;
	int heartCount;

	int whipLevel;


public:

	CSimon()
	{
		x = y = 0;
		this->SetPhysical(0.0f, 0.0f, 0.0f, 0.0f);

		this->SetSize(SIMON_WIDTH, SIMON_HEIGHT);
		this->maxVx = 0;

		untouchable = 0;
		untouchable_start = -1;

		invisible = 0;
		invisible_start = -1;

		currentWeapon = nullptr;
		currentSubWeaponType = -1;
		subWeaponLimit = 1;
		activeSubWeaponList = vector<CWeapon*>();

		whipLevel = 1;
		
		health = 5;
		heartCount = 50;

		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(SIMON_ANI_SET_ID));
	}

	void SetAx(float ax) { this->ax = ax; }
	void SetAy(float ay) { this->ay = ay; }
	void SetAccel(float ax, float ay) { this->ax = ax; this->ay = ay; }

	void SetMaxVx(float maxVx) { this->maxVx = maxVx; }

	void GetPhysical(float& vx, float& vy, float& ax, float& ay)	{ vx = this->vx; vy = this->vy; ax = this->ax; ay = this->ay;	}
	void SetPhysical(float vx, float vy, float ax, float ay) { this->vx = vx; this->vy = vy; this->ax = ax; this->ay = ay; }
	void SetDirectionX(int direction) { nx = direction; }
    int GetDirectionX() { return nx; }
	void SetDirectionY(int direction) { ny = direction; }
	int GetDirectionY() { return ny; }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	virtual void Render();

	//for collision
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithEnemy(CEnemy* enemy);
	void OnCollisionWithEnemyOnStair(CEnemy* enemy);
	void OnCollisionWithItem(CItem* item);

	void UpgradeWeapon();

	void UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void UpdateMoving(DWORD dt);

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; };
	int IsOverlappable() { return 1; }
	int CanCollisionWithObj(LPGAMEOBJECT objDests) override;

	//for untouchable mode
	void SetUntouchable(int untouchable) { this->untouchable = untouchable; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void FinishedUntouchable() { untouchable = 0; untouchable_start = 0; }
	int GetUntouchable() { return untouchable; }

	//for invisible mode
	void SetInvisible(int invisible) { this->invisible = invisible; }
	void StartInvisible() { invisible = 1; invisible_start = GetTickCount64(); }
	void FinishedInvisible() { invisible = 0; invisible_start = 0; }
	int GetInvisible() { return invisible; }

	//for go stair
	bool IsNearStairUp();
	bool IsNearStairDown();
	void CheckStairNearby(vector<LPGAMEOBJECT>* coObjects);
	CStair* GetNearbyStair() { return nearbyStair; }
	void SetOnStair(bool isonstair) { this->isOnStair = isonstair; }
	bool GetOnStair() { return isOnStair; }

	//for attack
	void SetCurrentWeapon(CWeapon* weapon) { this->currentWeapon = weapon; }
	CWeapon* GetCurrentWeapon() { return this->currentWeapon; }

	void SetSubWeapon(int subtype) { this->currentSubWeaponType = subtype; }
	vector<CWeapon*> GetSubWeaponList() const { return activeSubWeaponList; }

	int CanUseSubWeapon();
	void AddSubWeapon(CWeapon* subweapon);
	int GetCurrentSubType() { return this->currentSubWeaponType; }
	void RemoveAllSubWeapons();								//when simon dead, change scene
	void RenderSubWeapons();

	int getHeartCount() { return this->heartCount; }
	void addHeart(int heartcountadd) { this->heartCount += heartcountadd; }
	void spendHeart(int heartcountspend) { this->heartCount -= heartcountspend; }

	int getWhipLevel() { return whipLevel; }

	void TakenDamage(int damage);
	int IsAutoWalking() { return (isAutoWalking) ? 1 : 0; }
	int GetHealth() { return health; }
	void SetHealth(int hp) { health = hp; }
	CSimonState* GetSimonState();
	void SetState(CSimonState* state);
};