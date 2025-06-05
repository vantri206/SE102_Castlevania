#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"

#define MORNINGSTAR_STATE_NORMAL 0

#define ID_ANI_MONEYBAG_400 0
#define ID_ANI_MONEYBAG_700 1
#define ID_ANI_MONEYBAG_1000 2

#define MONEYBAG_WIDTH 15
#define MONEYBAG_HEIGHT 15

class CMoneyBag : public CGameObject
{
protected:
	int point;
	float ay;
	int hidden;
public:
	CMoneyBag();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();

	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	int IsOverlapable() { return 1; }

	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void LoadExtraSetting(vector<int> extra_settings);

	void SetMoneyBagAni();

	void StartAppearing();
};