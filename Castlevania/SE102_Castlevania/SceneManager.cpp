#include "SceneManager.h"
#include "Utils.h"
#include "Simon.h"
#include <PlayScene.h>
#include <fstream>
#include <Camera.h>
#include <SimonWalkingStairUp.h>
#include <SimonWalkingStairDown.h>
#include <MenuScene.h>

CSceneManager* CSceneManager::_instance = nullptr;

CSceneManager* CSceneManager::GetInstance()
{
    if (_instance == nullptr)  _instance = new CSceneManager();
    return _instance;
}

CSceneManager::CSceneManager()
{
    hud = new CHUD(CGame::GetInstance()->GetDirect3DDevice());
    transitionStart = -1;
}

void CSceneManager::LoadPlayer()
{
    this->player = new CSimon();
    this->player->SetState(new CSimonIdle(player));
}
void CSceneManager::AddScene(CScene* scene)
{
    int sceneid = scene->GetSceneId();
    if (sceneid >= 0 && sceneid < MAX_SCENES)
        scenes[sceneid] = scene;
}

void CSceneManager::LoadAllScenes(LPCWSTR filepath)
{
    ifstream f;
    f.open(filepath);
    if (!f.is_open())
    {
        //DebugOut(L"Cant open all scene file %s\n", filepath);
        return;
    }

    char str[MAX_TXT_LINE];
    while (f.getline(str, MAX_TXT_LINE))
    {
        string line(str);
        //DebugOut(L"[INFO] Load scene from file %s\n", line);
        if (line[0] == '#') continue;
        if (line.size() < 2) continue;

        vector<string> tokens = split(line);

        int typeScene = atoi(tokens[0].c_str());

        switch (typeScene)
        {
            case MENU_SCENE:
            {
                int sceneId = atoi(tokens[1].c_str());
                CMenuScene* scene = new CMenuScene();
                this->AddScene(scene);
                break;
            }
            case PLAY_SCENE:
            {
                int sceneId = atoi(tokens[1].c_str());
                int mapId = atoi(tokens[2].c_str());
                wstring mapFile = ToWSTR(tokens[3]);
                wstring objFile = ToWSTR(tokens[4]);

                DebugOut(L"[INFO] Loaded map from file: %s %s \n", mapFile.c_str(), objFile.c_str());

                CPlayScene* scene = new CPlayScene(sceneId, mapId, mapFile.c_str(), objFile.c_str());

                this->AddScene(scene);
                break;
            }
        }
    }
    f.close();
}

void CSceneManager::RequestChangeScene(int id, int entry)
{
    nextSceneId = id;
    nextSceneEntry = entry;
    isRequestedChangeScene = 1;
}

void CSceneManager::ChangeScene(int id, int entry)
{
    if (id < 0 || id >= MAX_SCENES || scenes[id] == nullptr)
    {
        DebugOut(L"Cant find scene has id %d\n", id);
        return;
    }

    currentSceneState = SCENE_STATE_LOADING;

    if (currentScene)
    {
        currentScene->UnloadResources();
    }
    
    currentScene = nullptr;
    currentSceneId = id;
    currentSceneEntry = entry;

    transitionStart = GetTickCount64();

    DebugOut(L"[SceneManager] Changed to scene %d (entry %d)\n", id, entry);
}


void CSceneManager::Update(DWORD dt)
{
    if (currentScene && currentSceneState != SCENE_STATE_LOADING)
        currentScene->Update(dt);
    else if (transitionStart != -1 && GetTickCount64() - transitionStart >= TRANSITION_SCENE_TIME)
    {
        currentScene = scenes[currentSceneId];
        CPlayScene* playScene = dynamic_cast<CPlayScene*>(currentScene);
        if (playScene)
            playScene->SetCurrentEntry(currentSceneEntry);
        currentScene->LoadResources();
        transitionStart = -1;
    }
    if (isRequestedReloadCheckpoint)
    {
        isRequestedReloadCheckpoint = 0;
        ReloadToCheckpoint();
    }
    else if (isRequestedChangeScene)
    {
        isRequestedChangeScene = 0;
        ChangeScene(nextSceneId, nextSceneEntry);
    }
    UpdateHUD();
}

void CSceneManager::Render()
{
    if (currentScene)
        currentScene->Render();
    if (transitionStart == -1 && currentScene->GetSceneType() != MENU_SCENE)
        hud->Render();
}

void CSceneManager::Clear()
{
    if (currentScene)
    {
        currentScene->UnloadResources();
        delete currentScene;
        currentScene = nullptr;
    }

    for (int i = 0; i < MAX_SCENES; ++i)
    {
        if (scenes[i])
        {
            delete scenes[i];
            scenes[i] = nullptr;
        }
    }

    currentSceneId = -1;
}

void CSceneManager::ReloadToCheckpoint()
{
    player->ReloadToCheckpoint();
   
    ChangeScene(currentSceneId, currentSceneEntry);
}

void CSceneManager::RequestReloadToCheckpoint()
{
    isRequestedReloadCheckpoint = 1;
}

void CSceneManager::UpdateHUD()
{
    hud->SetScore(player->GetScore());
    hud->SetPlayerHP(player->GetHealth());
    hud->SetStage(this->currentSceneId);
    hud->SetHeart(player->getHeartCount());
}

CSceneManager::~CSceneManager()
{
    Clear();
}