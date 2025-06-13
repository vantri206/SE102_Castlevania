#include "SmallHeart.h"

CSmallHeart::CSmallHeart()
{
    vx = SMALLHEART_SWING_SPEED;
    ay = HEART_GRAVITY;
    heartValue = SMALLHEART_HEART_VALUE;
    lastSwingTime = GetTickCount64();

    SetSize(SMALL_HEART_WIDTH, SMALL_HEART_HEIGHT);

    animation_set = CAnimationSets::GetInstance()->Get(SMALLHEART_ANI_SET_ID);
    ani_id = ID_ANI_SMALLHEART;
}

int CSmallHeart::getHeartValue()
{
    return heartValue;
}

void CSmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
    else if (e->nx != 0 && e->obj->IsBlocking())
    {
        this->SetVx(0.0f);
    }
}