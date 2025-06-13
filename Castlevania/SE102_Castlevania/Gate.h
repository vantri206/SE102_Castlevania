#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Portal.h"

#define GATE_STATE_CLOSE 0
#define GATE_STATE_OPEN 1

#define ANI_ID_GATE_CLOSE 0
#define ANI_ID_GATE_OPEN 1

#define GATE_CLOSE_WIDTH 8
#define GATE_CLOSE_HEIGHT 48

#define GATE_OPEN_WIDTH 24
#define GATE_OPEN_HEIGHT 48

class CGate : public CPortal
{
protected:
	int isActived;
	DWORD startOpen;
public:
	CGate();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void LoadExtraSetting(vector<int> extra_settings);

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Active();
};