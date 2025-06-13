#pragma once

#include "Scene.h"
#include "Simon.h"
#include <vector>
class CIntroScene : public CScene
{
protected:
    CSimon* player;
    vector<CGameObject*> objects;
    wstring objectFile;

    vector<sceneEntry*> SceneEntryList;
public:
    CIntroScene(wstring objectFile);
    void LoadResources();
    void UnloadResources();
    void Update(DWORD dt);
    void Render();
    void SetPlayer(CSimon* player) { this->player = player; }
};
