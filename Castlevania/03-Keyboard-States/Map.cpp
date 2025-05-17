#pragma once

#include "Map.h"
#include "Textures.h"
#include "Sprites.h"
#include "debug.h"
#include "Utils.h"
#include "GameDefine.h"

#include <fstream>
#include "Camera.h"

#define MAP_SIZE 0
#define TILE_SIZE 1
#define MATRIX_SIZE 2
#define TILES_COUNT 3
#define TILE_GRID_SIZE 4


CMap::CMap(int mapId, LPCWSTR mapFile)
{
	this->mapId = mapId;
	this->mapFile = mapFile;

	LoadMap();
}

void CMap::LoadMap()
{
	ifstream f;
	f.open(mapFile);

	if (!f.is_open())
	{
		DebugOut(L"[ERROR] Load map file failed\n");
		return;
	}

	char str[MAX_TXT_LINE];
	vector<string> tokens;

	//width, height

	for (int i = 0; i < 5;i++)
	{
		f.getline(str, MAX_TXT_LINE);
		string line(str);
		tokens = split(line);
		switch(i)
		{
		case MAP_SIZE:
			mapWidth = atoi(tokens[0].c_str());
			mapHeight = atoi(tokens[1].c_str());
			break;
		case TILE_SIZE:
			tileWidth = atoi(tokens[0].c_str());
			tileHeight = atoi(tokens[1].c_str());
			break;
		case MATRIX_SIZE:
			tileColumns = atoi(tokens[0].c_str());
			tileRows = atoi(tokens[1].c_str());
			break;
		case TILES_COUNT:
			tileCount = atoi(tokens[0].c_str());
			break;
		case TILE_GRID_SIZE:
			tilesetColumns = atoi(tokens[0].c_str());
			tilesetRows = atoi(tokens[1].c_str());
			break;
		}
	}

	CGame::GetInstance()->SetCurrentMap(this->mapId, mapWidth, mapHeight);
	CTextures::GetInstance()->AddTilesMap(mapId, tileWidth, tileHeight, tilesetColumns, tileCount);
	for (int i = 0; i < tileRows; i++)
	{
		f.getline(str, MAX_TXT_LINE);
		string line(str);
		tokens = split(line);

		vector<int> row;
		for (int j = 0; j < tileColumns; j++)
		{
			int tile_index = atoi(tokens[j].c_str());
			row.push_back(tile_index);
		}

		mapBackground.push_back(row);
	}
}

void CMap::Render()
{
	int cam_left = CCamera::GetInstance()->GetX();
	int cam_bottom = CCamera::GetInstance()->GetY();
	int cam_right = cam_left + CCamera::GetInstance()->GetWidth();
	int cam_top = cam_bottom + CCamera::GetInstance()->GetHeight();

	int columnleft = max(0, cam_left / tileWidth);
	int columnright = min(tileColumns, cam_right / tileWidth + 1);
	int rowtop = min(tileRows, cam_top / tileHeight);
	int rowbottom = max(0, cam_bottom / tileHeight + 1);

	float x, y;

	for (int i = rowbottom; i < rowtop; i++)
	{
		for (int j = columnleft; j < columnright; j++)
		{
			int tile_index = mapBackground[i][j];

			x = (j + 0.5f) * tileWidth;
			y = (tileRows - i - 0.5f) * tileHeight;

			//DebugOut(L"i, j : %f, %f, %d \n", x, y, tile_index);
			CTexture* tileTexture = CTextures::GetInstance()->Get(mapId * 1000 + tile_index);
			CGame::GetInstance()->Draw(x, y, -1, tileTexture, 0, 0, tileWidth - 1, tileHeight - 1);
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
	for (int i = 0; i < tileRows; i++)
		mapBackground[i].clear();
	mapBackground.clear();
}