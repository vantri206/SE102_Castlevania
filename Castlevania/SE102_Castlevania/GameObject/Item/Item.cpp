#include "Item.h"
#include <debug.h>

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (IsDeleted()) return;
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CItem::Render()
{
    if (IsDeleted()) return;
        animation_set->at(ani_id)->Render(x, y, nx, width, height);
}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - width / 4;
    t = y + height / 2;
    r = x + width / 4;
    b = y - height / 2;
}

void CItem::OnNoCollision(DWORD dt)
{
    y += vy * dt;
}

void CItem::OnCollisionWith(LPCOLLISIONEVENT e)
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