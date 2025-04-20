#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "GameDefine.h"
#include "debug.h"

#define GHOUL_WALKING_SPEED	0.15f

#define GHOUL_STATE_IDLE	0
#define GHOUL_STATE_WALK	1

#pragma region ANIMATION_ID

#define ANI_ID_GHOUL_IDLE 0
#define ANI_ID_GHOUL_WALK 1



class CGhoul : public CGameObject
{
protected:
	float maxVx, maxVy;
	float ax, ay;
	int nx, ny;
public:
	CGhoul() 
	{
		maxVx = GHOUL_WALKING_SPEED;
		maxVy = GHOUL_WALKING_SPEED;
		ax = 0.0f;
		ay = 0.0f;
		nx = 1, ny = 1;

		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(GHOUL_ANI_SET_ID));
	}
	void SetDirection(int direction) { nx = direction; }
	int GetDirection() { return nx; }
	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void SetState(int state);

};