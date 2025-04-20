#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "GameDefine.h"
#include "debug.h"

#define PANTHER_WALKING_SPEED 0.3f

#define PANTHER_STATE_IDLE	0
#define PANTHER_STATE_WALK	1

#pragma region ANIMATION_ID

#define ANI_ID_PANTHER_IDLE 0
#define ANI_ID_PANTHER_WALK 1


class CPanther : public CGameObject
{
protected:
	float maxVx, maxVy;
	float ax, ay;
	float startx, starty;
	int nx, ny;
public:
	CPanther()
	{
		maxVx = PANTHER_WALKING_SPEED;
		vy = PANTHER_WALKING_SPEED;
		ax = 0.0f;
		ay = 0.0f;
		nx = 1, ny = 1;
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(PANTHER_ANI_SET_ID));
	}
	void SetDirection(int direction) { nx = direction; }
	int GetDirection() { return nx; }
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Update(DWORD dt);
	void Render();
	void SetState(int state);

};