#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"

#define MORNINGSTAR_STATE_NORMAL 0

#define MORNINGSTAR_ANI_NORMAL 0

#define MORNINGSTAR_WIDTH 16
#define MORNINGSTAR_HEIGHT 16

class CMorningStar : public CGameObject
{
public:
	CMorningStar();
	void Render();
	void Update(DWORD dt) {}
	int IsBlocking() { return 0; }
	int IsColliable() { return 1; }
	int IsOverlapable() { return 1; }
};