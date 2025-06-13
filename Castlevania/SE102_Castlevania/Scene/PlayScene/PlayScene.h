#pragma once

#include <vector>
#include <Windows.h>
#include "Map.h"
#include "Scene.h"
#include "GameDefine.h"
#include <unordered_set>

class CGameObject;
class CGameEffect;
class QuadTree;
class CSimon;
class CEnemy;

struct sceneEntry
{
	float entryX, entryY;
};

class CPlayScene : public CScene
{
protected:

	wstring objectFile;

	CMap* SceneBG;
	int mapId;
	wstring mapFile;

	vector<CGameObject*> objects;
	std::unordered_set<CGameObject*> hiddenObjects;
	QuadTree* quadtree = nullptr;
	vector<CGameEffect*> effects;

	vector<sceneEntry*> SceneEntryList;
	int currentEntry;

	CSimon* player;
	CEnemy* boss;
public:
	CPlayScene(int id, int mapId, wstring mapFile, wstring objectFile);
	
	void LoadResources();
	void UnloadResources();

	void Update(DWORD dt);
	void Render();

	int GetCurrentMapHeight() { return max(SceneBG->GetHeight(), SCREEN_HEIGHT); }
	int GetCurrentMapWidth() { return SceneBG->GetWidth(); }

	void AddObject(CGameObject* obj);
	void AddHiddenObject(CGameObject* obj);
	void ClearObjects();

	void AddEffect(CGameEffect* effect);
	void ClearEffects();

	void SetPlayer(CSimon* player) { this->player = player; }
	void SetCurrentEntry(int entry) { currentEntry = entry; }

	CMap* GetSceneMap() { return SceneBG; }
	wstring GetObjectFile() { return objectFile; }

	CEnemy* GetBoss() { return boss; }
	vector<CGameObject*> GetAllObjects() { return objects; }
	~CPlayScene();
};
