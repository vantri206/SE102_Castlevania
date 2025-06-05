#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"

#define MORNINGSTAR_STATE_NORMAL 0

#define ID_ANI_MORNINGSTAR 0

#define MORNINGSTAR_WIDTH 16
#define MORNINGSTAR_HEIGHT 16

class CMorningStar : public CGameObject
{
protected: 
	float ay;
public:
	CMorningStar();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();

	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	int IsOverlapable() { return 1; }

	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& l, float& t, float& r, float& b);
};