#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "BreakableObject.h"

#define TORCH_STATE_BURN 0

#define TORCH_ANI_ID_BURN

class CTorch : public CBreakableObject
{
protected:
	int object_drop_id;
public:
	CTorch();
	void Render();
	int IsBlocking() { return 0; }
};