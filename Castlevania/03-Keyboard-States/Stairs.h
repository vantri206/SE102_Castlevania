#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CStair : public CGameObject
{
public:
	CStair();
	void Update(DWORD dt) {}
	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; }
};