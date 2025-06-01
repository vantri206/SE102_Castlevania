#pragma once

#include "Map.h"

class CSimon;
class CMap;
class CGameObject;
class CGameEffect;

class CScene
{
protected:
	int SceneId;

	LPCWSTR objectFile;

	CMap* SceneBG;

public:
	CScene(int Id, int mapId, LPCWSTR mapFile, LPCWSTR objectFile)
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
	void ClearObject();

	void AddEffect(CGameEffect* effect);
	void ClearEffects();

	CSimon* GetPlayer();
};
