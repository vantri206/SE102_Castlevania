#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define STAIR_WIDTH 32
#define STAIR_HEIGHT 4

class CStair : public CGameObject
{
private:
	int stair_direction;
	int horizontal_direction;
public:
	CStair();

	void Render() {}
	void Update(DWORD dt) {}

	int IsBlocking() { return 0; }

	void LoadExtraSetting(vector<int> extra_settings);
	int GetStairDirection();
	int GetHorizontalDirection();
};