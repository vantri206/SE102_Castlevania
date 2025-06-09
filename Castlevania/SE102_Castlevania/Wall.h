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
	int IsBlocking() { return 1; }
	int IsOverlappable() { return 0; }
	void LoadExtraSetting(vector<int> extra_settings);
};