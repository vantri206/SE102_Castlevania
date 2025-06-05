#pragma once
#include "PlayScene.h"
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
#include "Stair.h"
#include "Effect.h"
#include "MorningStar.h"

void CPlayScene::LoadScene()
{
	ifstream f;
	f.open(objectFile);

	if (!f.is_open())
	{
		DebugOut(L"[ERROR] Load scene objects failed\n");
		return;
	}

	int mapWidth = SceneBG->GetWidth();
	int mapHeight = SceneBG->GetHeight();
	quadtree = new QuadTree(mapWidth, mapHeight);

	char str[MAX_TXT_LINE];
	vector<string> tokens;

	while (f.getline(str, MAX_TXT_LINE))
	{
		string line(str);
		if (line[0] == '#' || line.length() < 6) continue;
		tokens = split(line);
		int objectId = atoi(tokens[0].c_str());
		int objectType = atoi(tokens[1].c_str());
		float x = atof(tokens[2].c_str());
		float y = atof(tokens[3].c_str());

		vector<int> extra_settings;

		for (size_t i = 4; i < tokens.size(); i++)
		{
			extra_settings.push_back(atoi(tokens[i].c_str()));
		}

		CGameObject* obj = NULL;
		if (objectType == SIMON) player->SetPosition(x, y);
		else
		{
			obj = CGameObject::CreateObject(objectId, objectType, extra_settings);

			if (obj != NULL)
			{
				obj->SetPosition(x, y);
				quadtree->Insert(obj);
			}
		}
	}
	quadtree->PrintTree();
	f.close();
}

void CPlayScene::LoadPlayer()
{
	player = new CSimon(0, 0);
	player->SetType(SIMON);
	player->SetState(new CSimonIdle(player));
	player->SetAnimationSet(CAnimationSets::GetInstance()->Get(SIMON_ANI_SET_ID));
}

void CPlayScene::Update(DWORD dt)
{
	RECT cam = CCamera::GetInstance()->GetCamRect();
	auto activeObjects = quadtree->GetObjectsInView(cam);
	for (auto obj : activeObjects)
		obj->Update(dt, &activeObjects);
	player->Update(dt, &activeObjects);
	for (auto effect : effects)
		effect->Update(dt);
}

void CPlayScene::Render()
{
	SceneBG->Render();
	RECT cam = CCamera::GetInstance()->GetCamRect();
	auto activeObjects = quadtree->GetObjectsInView(cam);
	for(auto obj : activeObjects)
	{
		if (obj == nullptr || obj->IsDeleted()) continue;
		obj->Render();
		obj->RenderBoundingBox();
	}

	player->Render();
	player->RenderBoundingBox();

	for (auto effect : effects)
		effect->Render();

	this->ClearObject();
	this->ClearEffects();
}

void CPlayScene::AddObject(CGameObject* obj)
{
	quadtree->Insert(obj);
}

void CPlayScene::ClearObject()
{
	RECT cam = CCamera::GetInstance()->GetCamRect();
	auto activeObjects = quadtree->GetObjectsInView(cam);
	for (auto obj : activeObjects)
	{
		if (obj != nullptr && obj->IsDeleted())
		{
			quadtree->Remove(obj);
			delete obj;
		}
	}
}

void CPlayScene::AddEffect(CGameEffect* effect)
{
	effects.push_back(effect);
}

void CPlayScene::ClearEffects()
{
	for (int i = 0; i < effects.size();)
	{
		if (effects[i]->IsFinished())
		{
			delete effects[i];
			effects.erase(effects.begin() + i);
		}
		else ++i;
	}
}

CSimon* CPlayScene::GetPlayer()
{
	return player;
}
