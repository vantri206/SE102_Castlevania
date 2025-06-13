#pragma once

#include "GameObject.h"

class CWaterDeadZone : public CGameObject
{
public:
	CWaterDeadZone();
	void Render() {}
	void Update(DWORD dt) {}

	int IsBlocking() { return 0; }

	void LoadExtraSetting(vector<int> extra_settings);
};