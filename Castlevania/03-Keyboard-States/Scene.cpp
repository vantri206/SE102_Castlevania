#pragma once
#include "Scene.h"
#include "debug.h"
#include "Utils.h"
#include "GameObject.h"
#include "GameDefine.h"
#include "Brick.h"
#include "Torch.h"
#include "QuadTree.h"
#include <fstream>
#include "Camera.h"
QuadTree* quadtree = NULL;
vector<CGameObject*> objects;

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
		float x = atof(tokens[1].c_str());
		float y = atof(tokens[2].c_str());
		float width = atoi(tokens[3].c_str());
		float height = atoi(tokens[4].c_str());	
		int animationSetId = atoi(tokens[5].c_str());
		CGameObject* obj = NULL;
		switch (objectId)
		{
		case BRICK_OBJECTS:
		obj = new CBrick();
		break;
		case TORCH_OBJECTS:
		obj = new CTorch();
		break;
		}
		if (obj != NULL)
		{
			obj->SetPosition(x, y);
			obj->SetSize(width, height);
			LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(animationSetId);
			obj->SetAnimationSet(ani_set);
			objects.push_back(obj);
			//DebugOut(L"[INFO] Load object %d at (%f, %f)\n", objectId, x, y);
		}
	}
	f.close();
	int mapWidth = SceneBG->GetWidth();
	int mapHeight = SceneBG->GetHeight();
	quadtree = new QuadTree(mapWidth, mapHeight, objects);
	//DebugOut(L"[INFO] Load scene %d objects\n");
	quadtree->PrintTree();
}

void CScene::Update(DWORD dt)
{
	RECT cam = CCamera::GetInstance()->GetCamRect();
	auto activeObjects = quadtree->GetObjectsInView(cam);

	for (auto obj : activeObjects)
		obj->Update(dt);
}

void CScene::Render()
{
	SceneBG->Render();
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render();
	}
}