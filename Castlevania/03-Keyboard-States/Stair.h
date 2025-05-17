#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CStair : public CGameObject
{
private:
	int stair_direction;
	int horizontal_direction;
public:
	CStair() {}
	void Render() {}
	void Update(DWORD dt) {}
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	int IsDirectionColliable(int nx, int ny) { return 1; }
	void LoadExtraSetting(vector<int> extra_settings);
	int GetStairDirection();
	int GetHorizontalDirection();
};