#pragma once
#include <unordered_map>

#include "Scene.h"
#include "GameDefine.h"

class CSimon;

class CSceneManager
{
private:
    static CSceneManager* _instance;

    CScene* scenes[MAX_SCENES] = {};
    CScene* currentScene = nullptr;
    int currentSceneId = -1;

    CSimon* player = nullptr;

    int isChangeScene = false;

public:
    void AddScene(CScene* scene);
    void LoadPlayer();
    void LoadAllScenes(LPCWSTR filepath);
    void ChangeScene(int id, int entry = 0);
    void Update(DWORD dt);
    void Render();

    CScene* GetCurrentScene() { return currentScene; }

    static CSceneManager* GetInstance();
    void Clear();

    CSimon* GetPlayer() { return player; }
    ~CSceneManager();
};
