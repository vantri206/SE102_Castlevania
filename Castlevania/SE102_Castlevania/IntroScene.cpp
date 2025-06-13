#include "IntroScene.h"
#include "SimonAutoWalking.h"
#include <fstream>
#include <ranges>
#include <Utils.h>

CIntroScene::CIntroScene(wstring objectFile)
{
	this->typeScene = INTRO_SCENE;
	this->objectFile = objectFile;
}

void CIntroScene::LoadResources()
{
	CSimon* player = CSceneManager::GetInstance()->GetPlayer();
	this->SetPlayer(player);
	SceneEntryList.clear();

	ifstream f;
	f.open(objectFile.c_str());

	if (!f.is_open())
	{
		DebugOut(L"[ERROR] Load scene objects failed\n");
		return;
	}

	char str[MAX_TXT_LINE];
	vector<string> tokens;

	while (f.getline(str, MAX_TXT_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;
		tokens = split(line);

		if (tokens[0] == "ENTRY")
		{
			sceneEntry* entry = new sceneEntry();
			entry->entryX = atof(tokens[1].c_str());
			entry->entryY = atof(tokens[2].c_str());
			SceneEntryList.push_back(entry);
			continue;
		}

		if (tokens.size() < 4) continue;

		int objectId = atoi(tokens[0].c_str());
		int objectType = atoi(tokens[1].c_str());
		float x = atof(tokens[2].c_str());
		float y = atof(tokens[3].c_str());

		vector<int> extra_settings;

		for (size_t i = 4; i < tokens.size(); i++)
		{
			extra_settings.push_back(atoi(tokens[i].c_str()));
		}

		CGameObject* obj = nullptr;
		obj = CGameObject::CreateObject(objectId, objectType, extra_settings);
		if (obj)
		{
			obj->SetPosition(x, y);
			objects.push_back(obj);
		}
	}
	CSceneManager::GetInstance()->SetCurrentSceneState(SCENE_STATE_RUNNING);
	f.close();
	player->SetPosition(SceneEntryList[0]->entryX, SceneEntryList[0]->entryY);
	player->SetState(new CSimonAutoWalking(player, SceneEntryList[1]->entryX, SceneEntryList[1]->entryY, 1, SIMON_STATE_INTRO));
}

void CIntroScene::UnloadResources()
{
	for (auto obj : objects)
	{
		delete obj;
		obj = nullptr;
	}
	objects.clear();
}

void CIntroScene::Update(DWORD dt)
{
	for (auto obj : objects)
		obj->Update(dt, &objects);
	player->Update(dt, &objects);
}

void CIntroScene::Render()
{
	CSprites::GetInstance()->Get(0)->Draw(170, 96, 1, 256, 192);
	player->Render();
	for (auto obj : objects)
		obj->RenderBoundingBox();
}