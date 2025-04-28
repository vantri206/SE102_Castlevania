#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CBrick : public CGameObject
{
public:
	CBrick();
	void Render() {}
	void Update(DWORD dt) {}
	int IsCollidable() { return 1; };
};