#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"

#define TORCH_STATE_BURN 0

class CTorch : public CGameObject
{
protected:
	int object_drop_id;
public:
	CTorch();
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void LoadExtraSetting(vector<int> extra_settings);
};