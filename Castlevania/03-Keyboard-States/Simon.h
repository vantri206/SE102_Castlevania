#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define SIMON_WALKING_SPEED		0.2f

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

#define SIMON_WIDTH 15
#define SIMON_HEIGHT 30

#define SIMON_SIZE 0.7f

class CSimon : public CGameObject
{
protected:
	float maxVx;
	float ax, ay;
	float startx, starty;
	bool isSitting;
	int ani_id;
public:
	CSimon(float x, float y) : CGameObject(x, y)
	{
		startx = x; starty = y;
		ax = 0.0f;
		ay = 0.0f;
		nx = 1;
		ny = 1;
		isSitting = false;
		ani_id = 0;
	}
	void SetDirectionX(int direction) { nx = direction; }
    int GetDirectionX() { return nx; }
	void SetDirectionY(int direction) { ny = direction; }
	int GetDirectionY() { return ny; }
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	int GetState();
	int GetVx() { return vx; };

	void SimonIdle();
	void SimonWalk();
	void SimonAttack();
	void SimonSit();
	void SimonWalkUp();

};