#pragma once

#include <vector>
#include <string>

#include "Tile.h"

using namespace std;

class CMap
{
protected:
	vector<CTile*> map;

	int mapId;

	LPCWSTR mapFile;

	int mapWidth;
	int mapHeight;

	int tileRows;
	int tileColumns;

	int tilesetRows;
	int tilesetColumns;

public:
	CMap(int mapId, LPCWSTR mapFile);

	void Render();

	int GetWidth();
	int GetHeight();

	void LoadMap();

	~CMap();

};