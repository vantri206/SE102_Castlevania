#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"

#define CANDLE_STATE_BURN 0

class CCandle : public CGameObject
{
protected:
	int object_drop_id;
public:
	CCandle();
	void Render();
	void Update(DWORD dt) {}
	void LoadExtraSetting(vector<int> extra_settings);
	int IsBlocking() { return 0; }
};