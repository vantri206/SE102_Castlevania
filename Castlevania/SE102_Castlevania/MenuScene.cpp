#include "MenuScene.h"
#include "GameObject.h"
#include "BatEffect.h"
#include "SceneManager.h"
#include "ButtonStart.h"

void CMenuScene::LoadResources()
{
	CMenuBatEffect* menubateffect = new CMenuBatEffect(menuCenterX + 105, menuCenterY - 15);
	effects.push_back(menubateffect);
	buttonstart = new CButtonStart(menuCenterX, menuCenterY);
	CSceneManager::GetInstance()->SetCurrentSceneState(SCENE_STATE_RUNNING);
}

void CMenuScene::UnloadResources()
{
	delete buttonstart;
	buttonstart = nullptr;
	for (auto effect : effects)
	{
		delete effect;
		effect = nullptr;
	}
	effects.clear();
}

void CMenuScene::Update(DWORD dt)
{
	buttonstart->Update(dt);
	for (auto effect : effects)
		effect->Update(dt);
	if (!isStartPressed && CGame::GetInstance()->IsKeyDown(DIK_RETURN))
	{
		isStartPressed = 1;
		startPressedTime = GetTickCount64();
		buttonstart->ButtonPressed();
	}
	if(isStartPressed && GetTickCount64() - startPressedTime >= 1000)
	CSceneManager::GetInstance()->RequestChangeScene(START_PLAYSCENE);
}

void CMenuScene::Render()
{
	CSprites::GetInstance()->Get(MENU_SCENE_BACKGROUND_ID)->Draw(menuCenterX, menuCenterY, POSITIVE_DIRECTION, 256.0f, 240.0f);
	for (auto effect : effects)
		effect->Render();
	buttonstart->Render();
}