#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "BreakableObject.h"
#include "GameSetting.h"

#define BREAKABLE_BRICK_ANI_BRICK1 0
#define BREAKABLE_BRICK_ANI_BRICK2 1
class CBreakableBrick : public CBreakableObject
{
protected:
	int brickType;
public:
	CBreakableBrick();
	int IsDirectionColliable(int nx, int ny);
	void Render();
	void LoadExtraSetting(vector<int> extra_settings);
	void TriggerBreakableBrickEffect();
	void OnHit();
};