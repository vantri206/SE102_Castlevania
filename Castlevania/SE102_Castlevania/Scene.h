#pragma once

#include <Windows.h>

class CScene 
{
protected:
    int SceneId;
public:
    CScene() {}

    virtual void LoadResources() = 0;

    virtual void UnloadResources() = 0;

    virtual void Update(DWORD dt) = 0;

    virtual void Render() = 0;

    virtual int GetSceneId() { return SceneId; }
    ~CScene() {}
};
