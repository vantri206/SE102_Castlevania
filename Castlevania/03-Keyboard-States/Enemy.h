#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#include "GameDefine.h"

class CEnemy : public CGameObject
{
protected:
	float maxVx, maxVy;
	float ax, ay;
	int nx, ny;
	int hp, attack;
public:
	CEnemy() {}
	void SetDirection(int direction) { nx = direction; }
	int GetDirection() { return nx; }
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	virtual void SetState(int state) = 0;
};