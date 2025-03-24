#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include "Animation.h"
#include "Animations.h"

using namespace std;

class CGameObject
{
protected:
    float x;
    float y;
    float width;
    float height;
    float vx;
    float vy;

    int nx;
    int ny;

    int state;

    CAnimationSet animations;
    LPANIMATION_SET animation_set;

public:
    float GetX() { return x; }
    float GetY() { return y; }
    float GetWidth() { return width; }
    float GetHeight() { return height; }

    void SetPosition(float x, float y) { this->x = x; this->y = y; }
    void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
    void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }

    void SetState(int state) { this->state = state; }
    int GetState() { return this->state; }

    CGameObject();
    CGameObject(float x, float y) : CGameObject() { this->x = x; this->y = y; }

    void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

    virtual void Update(DWORD dt) = 0;
    virtual void Render() = 0;

    virtual ~CGameObject();
};

typedef CGameObject* LPGAMEOBJECT;
