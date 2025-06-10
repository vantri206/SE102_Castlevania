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
	int IsDirectionColliable(int nx, int ny);
	void LoadExtraSetting(vector<int> extra_settings);
};