#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Effect.h"
#include "Game.h"
#include "ButtonStart.h"
#include <Windows.h>

#define START_PLAYSCENE 0

class CMenuScene : public CScene
{
protected:
	CButtonStart* buttonstart;
	vector<CGameEffect*> effects;
	int isStartPressed;
	DWORD startPressedTime;
	float menuCenterX, menuCenterY;
public:
	CMenuScene()
	{
		typeScene = MENU_SCENE;
		SceneId = MENU_SCENE_ID;
		isStartPressed = 0;
		menuCenterX = MENU_CENTERX;
		menuCenterY = MENU_CENTERY;
	}
	void LoadResources() override;
	void UnloadResources() override;
	void Update(DWORD dt) override;
	void Render() override;
};
