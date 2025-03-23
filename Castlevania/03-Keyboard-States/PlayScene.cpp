#include "PlayScene.h"
#include "Textures.h"
#include "Sprites.h"
#include "Utils.h"
#include "GameObject.h"
#include "GameDefine.h"

#include <fstream>

#define LOAD_RESOURCE_PLAYER 0
#define LOAD_RESOURCE_INFO 1
#define LOAD_RESOURCE_TILE 2


#define TILE_HEIGHT 32
#define TILE_WIDTH 32

vector<LPGAMEOBJECT> objects;

CPlayScene* CPlayScene::__instance = NULL;

void CPlayScene::Load()
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
	char str[MAX_TXT_LINE];

	while (f.getline(str, MAX_TXT_LINE))
	{
		string line(str);

		//DebugOut(L"[DEBUG] line: %S\n", line.c_str());

		if (line[0] == '#') continue;

		if (line == "[PLAYER]")
		{
			data = LOAD_RESOURCE_PLAYER; continue;
		}
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
		case LOAD_RESOURCE_PLAYER: _ParseSection_PLAYER(line); break;
		case LOAD_RESOURCE_INFO: _ParseSection_INFO(line); break;
		case LOAD_RESOURCE_TILE: _ParseSection_TILE(line); break;
		}
	}
	f.close();
}

void CPlayScene::_ParseSection_PLAYER(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	float startx = atoi(tokens[0].c_str());
	float starty = atoi(tokens[1].c_str());

	player = new CSimon(startx, starty);

	int ani_id = SIMON_ANI_SET_ID;
	LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(ani_id);
	player->SetAnimationSet(ani_set);
	player->SetState(SIMON_STATE_IDLE);

	objects.push_back(player);
	DebugOut(L"Done player %d\n", player->GetState());
}

void CPlayScene::_ParseSection_INFO(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	int width = atoi(tokens[0].c_str());
	int height = atoi(tokens[1].c_str());
	int offset = atoi(tokens[2].c_str());

	this->map_width = width;
	this->map_height = height;
	this->offset = offset;
}

void CPlayScene::_ParseSection_TILE(string line)
{
	CGame* game = CGame::GetInstance();
	int currentPlaySceneId = game->GetSceneId();
	LPTEXTURE texture = CTextures::GetInstance()->Get(currentPlaySceneId);


	vector<string> map_tile = split(line);


	for (int i = 0; i < map_tile.size(); i++)
	{
		int tile_index = atoi(map_tile[i].c_str());
		float x = i * TILE_WIDTH;
		float y = offset;

		int tilesheetWidth = texture->getWidth();
		int tilesheetHeight = texture->getHeight();

		int tileX = (tile_index % (tilesheetWidth / TILE_WIDTH)) * TILE_WIDTH;
		int tileY = (tile_index / (tilesheetWidth / TILE_WIDTH)) * TILE_HEIGHT;

		int left = tileX;
		int top = tileY;
		int right = tileX + TILE_WIDTH;
		int bottom = tileY + TILE_HEIGHT;

		CTile* tile = new CTile(x, y, left, top, right, bottom);
		map.push_back(tile);
	}
	offset += TILE_HEIGHT;
}

void CPlayScene::Update(DWORD dt)
{
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
}
void CPlayScene::Render()
{
	for (int i = 0; i < map.size(); i++)
		map[i]->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

CPlayScene* CPlayScene::GetInstance()
{
	if (__instance == NULL) __instance = new CPlayScene();
	return __instance;
}
