#include "SubWeaponItem.h"

CSubWeaponItem::CSubWeaponItem()
{
    vx = vy = 0.0f;
    width = height = 0;
    subWeaponType = -1;
    ay = DEFAULT_GRAVITY;
    animation_set = CAnimationSets::GetInstance()->Get(SUBWEAPONITEM_ANI_SET_ID);
}

void CSubWeaponItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += ay * dt;
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CSubWeaponItem::Render()
{
    animation_set->at(ani_id)->Render(x, y, nx, width, height);
}

void CSubWeaponItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - width / 4;
    t = y + height / 2;
    r = x + width / 4;
    b = y - height / 2;
}

void CSubWeaponItem::SetWeaponItem()
{
    switch (this->subWeaponType)
    {
    case DAGGER:
        this->SetSize(DAGGER_WIDTH, DAGGER_HEIGHT);
        this->SetAniId(ID_ANI_ITEM_DAGGER);
        break;
    case AXE:
        this->SetSize(AXE_WIDTH, AXE_HEIGHT);
        this->SetAniId(ID_ANI_ITEM_AXE);
        break;
    case HOLYWATERBOTTLE:
        this->SetSize(HOLYWATERBOTTLE_ITEM_WIDTH, HOLYWATERBOTTLE_ITEM_HEIGHT);
        this->SetAniId(ID_ANI_ITEM_HOLYWATER);
        break;
    }
}

void CSubWeaponItem::OnNoCollision(DWORD dt)
{
    y += vy * dt;
}

void CSubWeaponItem::OnCollisionWith(LPCOLLISIONEVENT e)
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

void CSubWeaponItem::LoadExtraSetting(vector<int> extra_settings)
{
    if (extra_settings.size() > 0)
        this->subWeaponType = extra_settings[0];
    this->SetWeaponItem();
}