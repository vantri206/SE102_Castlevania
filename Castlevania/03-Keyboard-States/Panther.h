#pragma once
#include "GameObject.h"
#include "Enemy.h"

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


class CPanther : public CEnemy
{
protected:
public:
	CPanther();
	void SetDirection(int direction) { nx = direction; }
	int GetDirection() { return nx; }
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Update(DWORD dt);
	void Render();
	void SetState(int state) {}

	void LoadExtraSetting(vector<int> extra_settings);
};