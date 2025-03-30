#pragma once

#include "Map.h"
#include "Textures.h"
#include "Sprites.h"
#include "debug.h"
#include "Utils.h"

#include <fstream>
#include "Camera.h"

#define TILE_HEIGHT 16
#define TILE_WIDTH 16

#define MAX_TXT_LINE 1024

CMap::CMap(int mapId, LPCWSTR mapFile)
{
	this->mapId = mapId;
	this->mapFile = mapFile;

	mapWidth = 0;
	mapHeight = 0;

	LoadMap();
}

void CMap::LoadMap()
{
	ifstream f;
	f.open(mapFile);
	DebugOut(L"[INFO] Start loading game from : %s \n", mapFile);

	if (!f.is_open())
	{
		DebugOut(L"[ERROR] Load map file failed\n");
		return;
	}

	char str[MAX_TXT_LINE];
	string loine;
	vector<string> tokens;

	//doc width, height

	f.getline(str, MAX_TXT_LINE);
	string line(str);
	tokens = split(line);

	mapWidth = atoi(tokens[0].c_str());
	mapHeight = atoi(tokens[1].c_str());

	tileRows = mapHeight / TILE_HEIGHT;
	tileColumns = mapWidth / TILE_WIDTH;

	tilesetRows = CTextures::GetInstance()->Get(this->mapId)->getHeight() / TILE_HEIGHT;
	tilesetColumns = CTextures::GetInstance()->Get(this->mapId)->getWidth() / TILE_WIDTH;

	for (int i = 0; i < tileRows; i++)
	{
		f.getline(str, MAX_TXT_LINE);
		string line(str);
		tokens = split(line);

		for (int j = 0; j < tileColumns; j++)
		{
			int tile_index = atoi(tokens[j].c_str());

			float x = j * TILE_WIDTH;
			float y = (tileRows - i - 1) * TILE_HEIGHT;

			int tileX = (tile_index % tilesetColumns) * TILE_WIDTH;
			int tileY = (tile_index / tilesetColumns) * TILE_HEIGHT;

			int left = tileX;
			int top = tileY;
			int right = tileX + TILE_WIDTH - 1;
			int bottom = tileY + TILE_HEIGHT - 1;

			CTile* tile = new CTile(x, y, left, top, right, bottom);
			map.push_back(tile);
		}
	}
}

void CMap::Render()
{
	for (int i = 0; i < map.size(); i++) 
	{
		if (CCamera::GetInstance()->IsInCamera(map[i])) 
		{
			map[i]->Render();
		}
	}
}

int CMap::GetWidth()
{
	return mapWidth;
}

int CMap::GetHeight()
{
	return mapHeight;
}

CMap::~CMap()
{
	map.clear();
}