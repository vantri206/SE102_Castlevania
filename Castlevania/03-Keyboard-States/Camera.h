#pragma once
#include "GameObject.h"
#include <algorithm>
#include "Game.h"

class CCamera {
private:
    static CCamera* __instance;   
    float x, y;                   
    float width, height;         

public:
    CCamera(float _x = 0, float _y = 0, float _width = 360, float _height = 192);
    static CCamera* GetInstance();
    void SetPosition(float newX, float newY, float mapWidth, float mapHeight);
    void SetSize(float width, float height);
    float GetX();
    float GetY();
    void SetX(float _x);
    void SetY(float _y);
    float GetWidth();
    float GetHeight();
    bool IsInCamera(CGameObject* obj);
    void Update(DWORD dt, CGameObject* target, float mapWidth, float mapHeight);
};
