#pragma once
#include <unordered_map>

#include "Scene.h"
#include "GameDefine.h"
#include "GameSetting.h"
#include "HUD.h"

#define SCENE_STATE_RUNNING 0
#define SCENE_STATE_LOADING 1

class CSimon;

class CSceneManager
{
protected:

    int currentSceneState;

    DWORD transitionStart;

    static CSceneManager* _instance;

    CScene* scenes[MAX_SCENES] = {};

    CScene* currentScene = nullptr;
    int currentSceneId = 0;
    int currentSceneEntry = 0;

    int isRequestedChangeScene = 0;
    int nextSceneId = 0;
    int nextSceneEntry = 0;

    CSimon* player = nullptr;

    int isChangeScene = false;

    CHUD* hud;

public:
    CSceneManager();
    static CSceneManager* GetInstance();

    void AddScene(CScene* scene);
    void LoadPlayer();
    void LoadAllScenes(LPCWSTR filepath);
    void RequestChangeScene(int id, int entry = 0);     //use for dont change scene while update objects -> crash
    void ChangeScene(int id, int entry = 0);
    void Update(DWORD dt);
    void Render();

    CScene* GetCurrentScene() { return currentScene; }
    void Clear();


    CSimon* GetPlayer() { return player; }

    void SetCurrentSceneState(int state) { currentSceneState = state; }

    ~CSceneManager();

    CHUD* GetHUD() { return hud; }
};
