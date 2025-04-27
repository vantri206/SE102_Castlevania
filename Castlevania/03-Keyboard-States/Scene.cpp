#pragma once
#include "Scene.h"
#include "Utils.h"
#include "GameDefine.h"
#include "QuadTree.h"
#include "Camera.h"
#include <fstream>

#include "Brick.h"
#include "Torch.h"
#include "Simon.h"
#include "Ghoul.h"
#include "Panther.h"
#include "Candle.h"

QuadTree* quadtree = NULL;
vector<CGameObject*> objects;
CSimon* player = NULL;

static CGameObject* CreateObject(int objectId, int objectType, vector<int> extra_settings)
{
	CGameObject* obj = NULL;
	switch (objectType)
	{
	case TORCH:
		obj = new CTorch();
		break;
	case CANDLE:
		obj = new CCandle();
		break;
	case GHOUL:
		obj = new CGhoul();
		break;
	case PANTHER:
		obj = new CPanther();
		break;
	case BRICK:
		obj = new CBrick();
		break;
	case PORTAL:
		obj = new CBrick();
		break;
	}
	obj->SetId(objectId);
	obj->LoadExtraSetting(extra_settings);
	return obj;
}

void CScene::LoadScene()
{
	ifstream f;
	f.open(objectFile);

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
		int objectId = atoi(tokens[0].c_str());
		int objectType = atoi(tokens[1].c_str());
		float x = atof(tokens[2].c_str());
		float y = atof(tokens[3].c_str());
		float width = atoi(tokens[4].c_str());
		float height = atoi(tokens[5].c_str());	

		vector<int> extra_settings;

		for (size_t i = 6; i < tokens.size(); i++)
		{
			extra_settings.push_back(atoi(tokens[i].c_str()));
		}

		CGameObject* obj = NULL;
		if (objectType == SIMON) player->SetPosition(x, y);
		else obj = CreateObject(objectId, objectType, extra_settings);

		if (obj != NULL)
		{
			obj->SetPosition(x, y);
			obj->SetSize(width, height);
			objects.push_back(obj);
			//DebugOut(L"[INFO] Load object %d at (%f, %f)\n", objectType, x, y);
		}
	}
	f.close();
	int mapWidth = SceneBG->GetWidth();
	int mapHeight = SceneBG->GetHeight();
	quadtree = new QuadTree(mapWidth, mapHeight, objects);
	//DebugOut(L"[INFO] Load scene %d objects\n");
	quadtree->PrintTree();
}

void CScene::LoadPlayer()
{
	player = new CSimon(0, 0);
	player->SetSize(SIMON_WIDTH, SIMON_HEIGHT);
	player->SetState(new CSimonIdle());
	player->SetAnimationSet(CAnimationSets::GetInstance()->Get(SIMON_ANI_SET_ID));
}

void CScene::Update(DWORD dt)
{
	RECT cam = CCamera::GetInstance()->GetCamRect();
	auto activeObjects = quadtree->GetObjectsInView(cam);

	for (auto obj : activeObjects)
		obj->Update(dt);
	player->Update(dt);
}

void CScene::Render()
{
	SceneBG->Render();
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render();
	}
	player->Render();
}
