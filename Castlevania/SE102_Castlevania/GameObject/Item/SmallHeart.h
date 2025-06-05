#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"

#define SMALL_HEART_WIDTH 8
#define SMALL_HEART_HEIGHT 8

#define ANI_ID_SMALLHEART 0

#define SMALLHEART_HEART_VALUE 1

#define SMALLHEART_SWING_TIME 200

#define HEART_GRAVITY -0.0075f
#define HEART_MAX_FALLSPEED -0.01f

#define SMALLHEART_SWING_SPEED 0.75f

class CSmallHeart : public CGameObject
{
protected:
    float heartValue;
    float ay;
    DWORD lastSwingTime;
public:
    CSmallHeart()
    {
        vx = SMALLHEART_SWING_SPEED;
        vy = 0.0f;
        ay = HEART_GRAVITY;
        heartValue = SMALLHEART_HEART_VALUE;
        lastSwingTime = GetTickCount64();

        SetSize(SMALL_HEART_WIDTH, SMALL_HEART_HEIGHT);
        animation_set = CAnimationSets::GetInstance()->Get(SMALLHEART_ANI_SET_ID);
    }

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
    {
        DWORD now = GetTickCount64();
        if (now - lastSwingTime > SMALLHEART_SWING_TIME)
        {
            nx = nx * (-1);
            lastSwingTime = now;
        }
        vx = SMALLHEART_SWING_SPEED * nx;
        vy += ay * dt;
        if (vy < HEART_MAX_FALLSPEED)
            vy = HEART_MAX_FALLSPEED;
        CCollision::GetInstance()->Process(this, dt, coObjects);
    }

    void Render()
    {
        animation_set->at(ANI_ID_SMALLHEART)->Render(x, y, nx, width, height);
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

    void CSmallHeart::OnNoCollision(DWORD dt)
    {
        x += vx * dt;
        y += vy * dt;
    }

    void CSmallHeart::OnCollisionWith(LPCOLLISIONEVENT e)
    {
        if (e->ny > 0 && e->obj->IsBlocking())
        {
            this->SetSpeed(0.0f, 0.0f);
        }
    }
};
