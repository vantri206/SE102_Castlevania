#include "Scene.h"
#include "Textures.h"
#include "Sprites.h"
#include "Utils.h"

#include <fstream>


#define LOAD_RESOURCE_INFO 1
#define LOAD_RESOURCE_TILE 2


#define TILE_HEIGHT 32
#define TILE_WIDTH 32

void CScene::Load()
{
	DebugOut(L"[INFO] Start loading game resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	if (!f.is_open())
	{
		DebugOut(L"[ERROR] Load resource file failed\n");
		return;
	}

	int data = -1;
	char str[1024];

	while (f.getline(str, 1024))
	{
		string line(str);

		//DebugOut(L"[DEBUG] line: %S\n", line.c_str());

		if (line[0] == '#') continue;

		if (line == "[INFO]")
		{
			data = LOAD_RESOURCE_INFO; continue;
		}
		if (line == "[TILE]")
		{
			data = LOAD_RESOURCE_TILE; continue;
		}
		switch (data)
		{
		case LOAD_RESOURCE_INFO: _ParseSection_INFO(line); break;
		case LOAD_RESOURCE_TILE: _ParseSection_TILE(line); break;
		}
	}
	f.close();
}

void CScene::_ParseSection_INFO(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	int width = atoi(tokens[0].c_str());
	int height = atoi(tokens[1].c_str());

	this->map_width = width;
	this->map_height = height;
}

void CScene::_ParseSection_TILE(string line)
{
	CGame* game = CGame::GetInstance();
	int currentMapId = game->GetCurrentMap();
	LPTEXTURE texture = CTextures::GetInstance()->Get(currentMapId);



	vector<string> map_tile = split(line);

	for (int i = 0; i < map_tile.size(); i++)
	{
		int tile_index = atoi(map_tile[i].c_str());
		float x = i * TILE_WIDTH;

		float y = col * TILE_HEIGHT;

		int tilesheetWidth = texture->getWidth();
		int tilesheetHeight = texture->getHeight();

		int tileX = float(tile_index % (tilesheetWidth / TILE_WIDTH)) * TILE_WIDTH;
		int tileY = float(tile_index / (tilesheetWidth / TILE_WIDTH)) * TILE_HEIGHT;

		int left = tileX;
		int top = tileY;
		int right = tileX + TILE_WIDTH;
		int bottom = tileY + TILE_HEIGHT;

		CTile* tile = new CTile(x, y, left, top, right, bottom);
		map.push_back(tile);
	}

	col++;
}

void CScene::Render()
{
	DebugOut(L"Map size: %d \n", map.size());
	for (int i = 0; i < map.size(); i++)
		map[i]->Render();
}