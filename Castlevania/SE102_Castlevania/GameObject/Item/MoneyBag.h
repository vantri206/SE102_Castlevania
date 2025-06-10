#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "GameSetting.h"
#include "Item.h"

#define MONEYBAG_STATE_IDLE 0
#define MONEYBAG_STATE_SPAWN 1

#define ID_ANI_MONEYBAG_400 0
#define ID_ANI_MONEYBAG_700 1
#define ID_ANI_MONEYBAG_1000 2

class CMoneyBag : public CItem
{
protected:
	int point;
	float ay;

	DWORD startSpawn;
public:
	CMoneyBag();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void LoadExtraSetting(vector<int> extra_settings);

	void SetMoneyBagAni();

	void StartSpawning();
	void FinishedSpawning();
	int isSpawning() { return (state == MONEYBAG_STATE_SPAWN); }
};