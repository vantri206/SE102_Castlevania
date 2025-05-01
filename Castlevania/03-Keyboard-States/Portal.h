#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CPortal : public CGameObject
{
protected:
	int sceneId;
public:
	CPortal();
	void Render() {}
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void SetSceneId(int id) { sceneId = id; }
	int IsBlocking() { return 0; }
};