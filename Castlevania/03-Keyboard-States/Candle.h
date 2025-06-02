#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "BreakableObject.h"

#define CANDLE_STATE_BURN 0

#define CANDLE_ANI_BURN 0

#define CANDLE_WIDTH 8
#define CANDLE_HEIGHT 16

class CCandle : public CBreakableObject
{
public:
	CCandle();
	void Render();
	void Update(DWORD dt) {}
	int IsBlocking() { return 0; }
	int IsColliable() { return 1; }
};