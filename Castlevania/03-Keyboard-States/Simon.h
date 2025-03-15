#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define SIMON_WALKING_SPEED		0.1f

#define SIMON_STATE_IDLE	0
#define SIMON_STATE_WALK	1
#define SIMON_STATE_JUMP 2
#define SIMON_STATE_SIT 3
#define SIMON_STATE_ATTACK 4



#pragma region ANIMATION_ID

#define ID_ANI_SIMON_IDLE 0
#define ID_ANI_SIMON_WALK 1
#define ID_ANI_SIMON_JUMP 2
#define ID_ANI_SIMON_SIT 3
#define ID_ANI_SIMON_ATTACK 4


#define SIMON_WIDTH 15
#define SIMON_HEIGHT 30


class CSimon : public CGameObject
{
protected:
	float maxVx;
	float ax, ay;
	float startx, starty;
	int nx;
public:
	CSimon(float x, float y) : CGameObject(x, y)
	{
		startx = x; starty = y;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
		nx = 1;
	}
	void SetDirection(int direction) { nx = direction; }
    int GetDirection() { return nx; }
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};