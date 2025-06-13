#pragma once
#include "GameObject.h"
#include <memory>

#include "SimonState.h"
#include "SimonIdle.h"
#include "SimonHurt.h"
#include "SimonFalling.h"
#include "Fireball.h"
#include "Brick.h"
#include "Enemy.h"

#include "SimonDie.h"
#include "debug.h"
#include "GameDefine.h"
#include "GameSetting.h"
#include "Stair.h"

#include "Weapon.h"
#include "Item.h"

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
#define ID_ANI_SIMON_INTRO 14
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
	int isOnStair = 0;

	CWeapon* currentWeapon;
	int currentSubWeaponType;
	int subWeaponLimit;
	vector<CWeapon*> activeSubWeaponList;

	bool isAutoWalking;

	int health;
	int heartCount;

	int isDrowning;

	int isDead;

	int whipLevel;

	int score;
public:

	CSimon()
	{
		x = y = 0;
		this->SetPhysical(0.0f, 0.0f, 0.0f, 0.0f);

		this->SetSize(SIMON_WIDTH, SIMON_HEIGHT);
		this->maxVx = SIMON_WALKING_SPEED;

		untouchable = 0;
		untouchable_start = -1;

		invisible = 0;
		invisible_start = -1;

		currentWeapon = nullptr;
		currentSubWeaponType = -1;
		subWeaponLimit = 1;
		activeSubWeaponList = vector<CWeapon*>();

		nearbyStair = nullptr;

		whipLevel = 1;
		
		health = 16;
		heartCount = 5;

		isDrowning = 0;

		isDead = 0;

		score = 0;

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
	void OnCollisionWithBullet(CFireball* fireball);

	void UpgradeWeapon();

	void UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void UpdateMoving(DWORD dt);

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; };
	int IsOverlappable() { return 1; }
	int CanCollisionWithObj(LPGAMEOBJECT objDests);
	int CanOverlapWithObj(LPGAMEOBJECT objDests);

	//for untouchable mode
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void FinishedUntouchable() { untouchable = 0; untouchable_start = 0; }
	int IsUntouchable() { return untouchable; }

	//for invisible mode
	int IsInvisible() { return invisible; }
	void StartInvisible() { invisible = 1; invisible_start = GetTickCount64(); }
	void FinishedInvisible() { invisible = 0; invisible_start = 0; }

	//for go stair
	bool IsNearStairUp();
	bool IsNearStairDown();
	void CheckStairNearby(vector<LPGAMEOBJECT>* coObjects);
	CStair* GetNearbyStair() { return nearbyStair; }
	void SetNearbyStair(CStair* stair) { nearbyStair = stair; }
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
	void StartDrowning();
	int IsDrowning() { return isDrowning; }
	void SetState(CSimonState* state);

	int IsDead();
	void StartDead();

	int GetScore();
	void SetScore(int score) { this->score = score; }

	void ReloadToCheckpoint();
};