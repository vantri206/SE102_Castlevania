#pragma once

#include <vector>
#include <Windows.h>
#include "Map.h"
#include <unordered_set>

class CSimon;
class CGameObject;
class CGameEffect;
class QuadTree;
class CPlayScene
{
protected:
	int SceneId;

	LPCWSTR objectFile;

	CMap* SceneBG;

	std::unordered_set<CGameObject*> hiddenObj;
	QuadTree* quadtree = nullptr;
	CSimon* player = nullptr;
	vector<CGameEffect*> effects;

public:
	CPlayScene(int Id, int mapId, LPCWSTR mapFile, LPCWSTR objectFile)
	{
		this->SceneId = Id;

		this->objectFile = objectFile;

		this->SceneBG = new CMap(mapId, mapFile);
		
		this->LoadPlayer();

		this->LoadScene();

	}

	void LoadPlayer();
	void LoadScene();
	void Update(DWORD dt);
	void Render();

	int GetCurrentMapHeight() { return SceneBG->GetHeight(); }
	int GetCurrentMapWidth() { return SceneBG->GetWidth(); }

	void AddObject(CGameObject* obj);
	void AddHiddenObject(CGameObject* obj);
	void ClearObject();

	void AddEffect(CGameEffect* effect);
	void ClearEffects();

	CSimon* GetPlayer();
};
