#include "SceneManager.h"
#include "Utils.h"
#include "Simon.h"
#include <PlayScene.h>
#include <fstream>
#include <Camera.h>

CSceneManager* CSceneManager::_instance = nullptr;

CSceneManager* CSceneManager::GetInstance()
{
    if (_instance == nullptr)  _instance = new CSceneManager();
    return _instance;
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
        int sceneId = atoi(tokens[1].c_str());
        int mapId = atoi(tokens[2].c_str());
        wstring mapFile = ToWSTR(tokens[3]);
        wstring objFile = ToWSTR(tokens[4]);

        DebugOut(L"[INFO] Loaded map from file: %s %s \n", mapFile.c_str(), objFile.c_str());

        CPlayScene* scene = new CPlayScene(sceneId, mapId, mapFile.c_str(), objFile.c_str());

        this->AddScene(scene);
    }
    f.close();
}

void CSceneManager::ChangeScene(int id, int entry)
{
    if (id < 0 || id >= MAX_SCENES || scenes[id] == nullptr)
    {
        DebugOut(L"Cant find scene has id %d\n", id);
        return;
    }

    if (currentScene)
    {
        currentScene->UnloadResources();
    }
    
    currentScene = nullptr;
    currentSceneId = id;
    nextSceneEntry = entry;

    transitionStart = GetTickCount64();

    DebugOut(L"[SceneManager] Changed to scene %d (entry %d)\n", id, entry);
}


void CSceneManager::Update(DWORD dt)
{
    DWORD now = GetTickCount64();
    if (currentScene)
            currentScene->Update(dt);
     if (transitionStart != - 1 && GetTickCount64() - transitionStart >= TRANSITION_SCENE_TIME)
     {
        currentScene = scenes[currentSceneId];
        currentScene->LoadResources();
        CPlayScene* playScene = dynamic_cast<CPlayScene*>(currentScene);
        if (playScene)
            playScene->SetCurrentEntry(nextSceneEntry);
        transitionStart = -1;
     }
}

void CSceneManager::Render()
{
    if (currentScene)
        currentScene->Render();
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

CSceneManager::~CSceneManager()
{
    Clear();
}