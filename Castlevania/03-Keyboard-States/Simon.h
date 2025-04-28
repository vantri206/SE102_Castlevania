#pragma once
#include "GameObject.h"
#include <memory>
#include "SimonState.h"
#include "SimonIdle.h"
#include "SimonHurt.h"
#include "debug.h"
#include "GameDefine.h"


#define SIMON_WALKING_SPEED		0.2f
#define SIMON_HURT_VX 0.2f    // T?c ?? v?ng ngang
#define SIMON_HURT_VY 0.4f    // T?c ?? v?ng lên
#define SIMON_HURT_TIME 300   // Th?i gian v?ng ra (ms)
#define SIMON_UNTOUCHABLE_TIME 1000 // Th?i gian b?t t? sau khi b? th??ng (ms)
#define SIMON_JUMP_SPEED 0.3f
#define JUMP_DURATION 500 // ms
#define GRAVITY 0.001f

#define SIMON_STATE_IDLE	0
#define SIMON_STATE_WALK	1
#define SIMON_STATE_JUMP	2
#define SIMON_STATE_SIT		3
#define SIMON_STATE_ATTACK	4
#define SIMON_STATE_GO_UP	5
#define SIMON_STATE_GO_DOWN 6



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

#define SIMON_WIDTH 16
#define SIMON_HEIGHT 32

#define SIMON_SIZE 0.5f

class CSimon : public CGameObject
{
protected:

	float maxVx;
	float ax, ay;

	unique_ptr<CSimonState> currentState;
	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
public:
	CSimon(float x, float y)
	{
		this->x = x;
		this->y = y;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		nx = NEGATIVE_DIRECTION;
		ny = 1;
		
		currentState = make_unique<CSimonIdle>();
	}

	void SetDirectionX(int direction) { nx = direction; }
    int GetDirectionX() { return nx; }
	void SetDirectionY(int direction) { ny = direction; }
	int GetDirectionY() { return ny; }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithEnemy(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	BOOLEAN IsOnPlatform() { return isOnPlatform; }
	CSimonState* GetState();
	void SetState(CSimonState* state);

};