#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CWall : public CGameObject
{
protected:
	int active;
public:
	CWall();
	void Render() {}
	void Update(DWORD dt) {}
	void LoadExtraSetting(vector<int> extra_settings);

	int IsBlocking() { return active; }
	int IsOverlappable() { return 1; }
	void Active() { this->ActiveWall(); }
	void ActiveWall() { active = 1; }
};