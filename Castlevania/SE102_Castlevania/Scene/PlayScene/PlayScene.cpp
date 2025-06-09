#include "PlayScene.h"
#include "Utils.h"
#include "Camera.h"
#include "Simon.h"
#include "QuadTree.h"
#include "Map.h"
#include "GameObject.h"
#include "Effect.h"
#include <fstream>

CPlayScene::CPlayScene(int id, int mapId, wstring mapFile, wstring objectFile)
{
    this->SceneId = id;

	this->objectFile = objectFile;

	this->mapId = mapId;

	this->mapFile = mapFile;
}

void CPlayScene::LoadResources() 
{
	CSimon* player = CSceneManager::GetInstance()->GetPlayer();
	this->SetPlayer(player);

	SceneBG = new CMap(mapId, mapFile.c_str());
	SceneEntryList.clear();

	ifstream f;
	f.open(objectFile.c_str());

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
			quadtree->Insert(obj);
		}
	}
	if (currentEntry >= 0 && currentEntry < SceneEntryList.size())
	{
		sceneEntry* entry = SceneEntryList[currentEntry];
		if (entry)
		{
			player->SetPosition(entry->entryX, entry->entryY);
			//DebugOut(L"[INFO] Player position in new scene: %f %f\n", entry->entryX, entry->entryY);
		}
	}
	else
	{
		DebugOut(L"Cant find entry posittion %d\n", currentEntry);
	}
	quadtree->PrintTree();
	f.close();
}

void CPlayScene::UnloadResources()
{
    if (quadtree)
    {
        auto allObjects = quadtree->GetAllObjects();
        for (auto obj : allObjects)
        {
            delete obj;
			obj = nullptr;
        }
        delete quadtree;
        quadtree = nullptr;
    }

    for (auto e : effects) 
    {
        delete e;
    }

    effects.clear();

    hiddenObjects.clear();

    if(SceneBG)
    {
        delete SceneBG;
        SceneBG = nullptr;
    }
}

void CPlayScene::Update(DWORD dt)
{
	RECT cam = CCamera::GetInstance()->GetCamRect();

	auto activeObjects = quadtree->GetObjectsInView(cam);
	for (auto obj : activeObjects)
		obj->Update(dt, &activeObjects);
	if(player) player->Update(dt, &activeObjects);

	for (auto effect : effects)
		effect->Update(dt);
}

void CPlayScene::Render()
{
	RECT cam = CCamera::GetInstance()->GetCamRect();
	auto activeObjects = quadtree->GetObjectsInView(cam);
	vector<LPGAMEOBJECT> hiddenObj, normalObj, enemyObj;

	for (auto obj : activeObjects)
	{
		if (obj == nullptr || obj->IsDeleted()) continue;
		if (hiddenObjects.find(obj) != hiddenObjects.end())
		{
			hiddenObj.push_back(obj);
		}
		else if (dynamic_cast<CEnemy*>(obj))
		{
			enemyObj.push_back(obj);
		}
		else normalObj.push_back(obj);
	}
	
	SceneBG->RenderBackground();

	for (auto obj : hiddenObj)
		obj->Render();

	SceneBG->RenderForeground();

	for (auto obj : normalObj)
		obj->Render();

	for (auto obj : enemyObj)
		obj->Render();
	
	for (auto obj : activeObjects)
		obj->RenderBoundingBox();

	if (player) player->Render();

	for (auto effect : effects)
		effect->Render();

	this->ClearObjects();
	this->ClearEffects();
}

void CPlayScene::AddObject(CGameObject* obj)
{
	quadtree->Insert(obj);
}

void CPlayScene::AddHiddenObject(CGameObject* obj)
{
	hiddenObjects.insert(obj);
}

void CPlayScene::ClearObjects()
{
	auto allObjects = quadtree->GetAllObjects();
	for (auto obj : allObjects)
	{
		if (obj && obj->IsDeleted())
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

CPlayScene::~CPlayScene()
{
    delete SceneBG;
	auto allObjects = quadtree->GetAllObjects();
	for (auto obj : allObjects)
	{
		if (obj != nullptr && obj->IsDeleted())
		{
			quadtree->Remove(obj);
			delete obj;
		}
	}
    delete quadtree;
    delete player;
    for (auto effect : effects)
        delete effect;
	effects.clear();
}
