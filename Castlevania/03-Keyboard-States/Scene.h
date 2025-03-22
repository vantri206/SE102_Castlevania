#pragma once
#include <vector>
#include <string>

#include "Sprite.h"
#include "Textures.h"
#include "debug.h"


using namespace std;

class CTile
{
protected:
	float x;
	float y;

	int left;
	int top;
	int right;
	int bottom;

public:

	CTile::CTile(float _x, float _y, int _left, int _top, int _right, int _bottom)
	{
		x = _x;
		y = _y;
		left = _left;
		top = _top;
		right = _right;
		bottom = _bottom;
	}	

	void CTile::Render()
	{
		int mapId = CGame::GetInstance()->GetCurrentMap();
		LPTEXTURE tex = CTextures::GetInstance()->Get(mapId);
		DebugOut(L"Tile: %f %f %d %d %d %d\n", x, y, left, top, right, bottom);
		CGame::GetInstance()->Draw(x, y, 1, tex, left, top, right, bottom);
	}
};

class CScene
{
protected:

	vector<CTile*> map;

	int map_width;
	int map_height;

	int id;
	LPCWSTR sceneFilePath;

	int col;

public:
	CScene(int _id, LPCWSTR filePath)
	{
		id = _id;
		sceneFilePath = filePath;
		col = 0;
	}

	void Load();
	void Render();

	int GetWidth(){ return map_width; };
	int GetHeight() { return map_height; };

	int GetSceneId() { return id; }

	void _ParseSection_INFO(string line);
	void _ParseSection_TILE(string line);

	~CScene();

};