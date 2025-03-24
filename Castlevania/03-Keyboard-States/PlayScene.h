#pragma once
#include <vector>
#include <string>

#include "SampleKeyEventHandler.h"
#include "Sprite.h"
#include "Textures.h"
#include "debug.h"
#include "Scene.h"

#include "Simon.h"

using namespace std;

class CTile : public CGameObject
{
protected:
	int left;
	int top;
	int right;
	int bottom;

public:
	CTile(float _x, float _y, int _left, int _top, int _right, int _bottom)
		: CGameObject(_x, _y), left(_left), top(_top), right(_right), bottom(_bottom)
	{
		width = right - left;  
		height = bottom - top; 
	}

	void Update(DWORD dt) override {
	}

	void Render() override {
		int sceneId = CGame::GetInstance()->GetSceneId();
		LPTEXTURE tex = CTextures::GetInstance()->Get(sceneId);

		CGame::GetInstance()->Draw(x, y, -1, tex, left, top, right, bottom, 1);
	}
};

class CPlayScene : public CScene
{
protected:

	static CPlayScene* __instance;

	CSimon* player;

	vector<CTile*> map;

	int map_width;
	int map_height;

	int offset;

public:
	CPlayScene()
	{
		key_handler = NULL;
		player = NULL;
	}
	CPlayScene::CPlayScene(int _id, LPCWSTR filePath) : CScene(_id, filePath)
	{
		key_handler = new CSampleKeyHandler(this);
		player = NULL;
	}

	void Load();

	void Render();

	void Update(DWORD dt);

	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }

	int GetWidth() { return map_width; };
	int GetHeight() { return map_height; };

	int GetPlaySceneId() { return id; }

	CSimon* getPlayer() { return player; }

	void _ParseSection_PLAYER(string line);
	void _ParseSection_INFO(string line);
	void _ParseSection_TILE(string line);

	static CPlayScene* GetInstance();

	~CPlayScene();

};
