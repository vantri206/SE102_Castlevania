#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"

#define BIG_HEART_WIDTH 12
#define BIG_HEART_HEIGHT 10

#define ANI_ID_BIGHEART 0
#define BIGHEART_HEART_VALUE 5

#define HEART_GRAVITY -0.0075f
#define HEART_MAX_FALLSPEED -0.01f

class CBigHeart : public CGameObject 
{
protected:
    float heartValue;
    float ay;
public:
    CBigHeart() 
    {
        SetSize(BIG_HEART_WIDTH, BIG_HEART_HEIGHT);
        vx = vy = 0.0f;
        ay = HEART_GRAVITY;           
        heartValue = BIGHEART_HEART_VALUE;
        animation_set = CAnimationSets::GetInstance()->Get(BIGHEART_ANI_SET_ID);
    }

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
    {
        vy += ay * dt;
        if (vy < HEART_MAX_FALLSPEED)
            vy = HEART_MAX_FALLSPEED;
        CCollision::GetInstance()->Process(this, dt, coObjects);
    }

    void Render()
    {
        animation_set->at(ANI_ID_BIGHEART)->Render(x, y, nx, width, height);
    }
    
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b)
    {
        l = x - width / 4;
        t = y + height / 2;
        r = x + width / 4;
        b = y - height / 2;
    }

    virtual int IsBlocking() { return 0; }
    virtual int IsOverlappable() { return 1; }
    virtual int IsCollidable() { return 1; };

    void CBigHeart::OnNoCollision(DWORD dt)
    {
        y += vy * dt;
    }

    void CBigHeart::OnCollisionWith(LPCOLLISIONEVENT e)
    {
        if (e->ny > 0 && e->obj->IsBlocking())
        {
            vy = 0.0f;
        }
        else if (e->nx != 0 && e->obj->IsBlocking())
        {
            vx = 0.0f;
        }
    }
};
