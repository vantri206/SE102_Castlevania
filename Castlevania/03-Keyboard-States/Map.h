#pragma once

#include <vector>
#include <string>

#include "Texture.h"
#include "Textures.h"

using namespace std;

class CMap
{
protected:

	vector<vector<int>> mapBackground;

	int mapId;

	LPCWSTR mapFile;

	int mapWidth;
	int mapHeight;

	int tileWidth;
	int tileHeight;

	int tileRows;
	int tileColumns;

	int tilesetRows;
	int tilesetColumns;

	int tileCount;

public:
	CMap(int mapId, LPCWSTR mapFile);

	void Render();

	int GetWidth();
	int GetHeight();

	void LoadMap();

	~CMap();

};