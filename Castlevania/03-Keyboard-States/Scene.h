#pragma once

#include <Windows.h>
#include "Map.h"
class CMap;

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

		this->LoadScene();
	}

	void LoadScene();
	void Update(DWORD dt);
	void Render();
};
