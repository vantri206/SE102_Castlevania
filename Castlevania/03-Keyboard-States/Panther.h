#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define PANTHER_WALKING_SPEED	0.3f

#define PANTHER_STATE_IDLE	0
#define PANTHER_STATE_WALK	1

#pragma region ANIMATION_ID

#define ANI_ID_PANTHER_IDLE 0
#define ANI_ID_PANTHER_WALK 1


#define PANTHER_WIDTH 15
#define PANTHER_HEIGHT 30

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400


class CPANTHER : public CGameObject
{
protected:
	float maxVx, maxVy;
	float ax, ay;
	float startx, starty;
	int nx, ny;
public:
	CPANTHER(float x, float y)
	{
		maxVx = PANTHER_WALKING_SPEED;
		vy = PANTHER_WALKING_SPEED;
		ax = 0.0f;
		ay = 0.0f;
		nx = 1, ny = 1;
	}
	void SetDirection(int direction) { nx = direction; }
	int GetDirection() { return nx; }
	void Update(DWORD dt);
	void Render();
	void SetState(int state);

};