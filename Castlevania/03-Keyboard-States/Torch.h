#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "BreakableObject.h"

#define TORCH_STATE_BURN 0

#define TORCH_ANI_ID_BURN

#define TORCH_WIDTH 16
#define TORCH_HEIGHT 32

class CTorch : public CBreakableObject
{
public:
	CTorch();
	void Render();
	void Update(DWORD dt) {}
	int IsBlocking() { return 0; }
};