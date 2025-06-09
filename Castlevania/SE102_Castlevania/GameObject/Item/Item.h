#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"

class CItem : public CGameObject
{
protected:
    float ay;
public:
    CItem()
    {
        ay = 0;
    }
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

    void Render();

    void GetBoundingBox(float& l, float& t, float& r, float& b);

    virtual int IsBlocking() { return 0; }
    virtual int IsOverlappable() { return 1; }
    virtual int IsCollidable() { return 1; };

    void OnNoCollision(DWORD dt);

    void OnCollisionWith(LPCOLLISIONEVENT e);

    virtual void StartSpawning() {}
    virtual void FinishedSpawning() {}
};
