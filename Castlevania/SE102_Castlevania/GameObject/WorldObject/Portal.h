#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CPortal : public CGameObject
{
protected:
	int sceneId;
	int sceneEntryId;
public:
	CPortal();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
	virtual void Render() {}
	virtual void LoadExtraSetting(vector<int> extra_settings);

	int IsBlocking() { return 0; }
	int IsOverlappable() { return 1; }

	void ChangeScene();
	virtual void Active();
};