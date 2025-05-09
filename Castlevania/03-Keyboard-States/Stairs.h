#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CStairs : public CGameObject
{
public:
	CStairs();
	void Update(DWORD dt) {}
	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; }
};