#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CWall : public CGameObject
{
public:
	CWall();
	void Render() {}
	void Update(DWORD dt) {}
	void LoadExtraSetting(vector<int> extra_settings);

	int IsOverlappable() { return 1; }
};