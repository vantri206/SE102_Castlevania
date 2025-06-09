#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "BreakableObject.h"

#define BREAKABLE_BRICK_ANI_BRICK1 0
#define BREAKABLE_BRICK_ANI_BRICK2 1

#define BREAKABLE_BRICK_WIDTH 16
#define BREAKABLE_BRICK_HEIGHT 16

class CBreakableBrick : public CBreakableObject
{
protected:
	int brickType;
public:
	CBreakableBrick();
	int IsBlocking() { return 1; }
	int IsOverlappable() { return 0; }
	int IsDirectionColliable(int nx, int ny);
	void Render();
	void LoadExtraSetting(vector<int> extra_settings);
};