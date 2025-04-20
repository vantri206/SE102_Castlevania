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
	void SetSceneId(int id) { sceneId = id; }
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};