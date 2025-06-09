#include "SubWeaponItem.h"

CSubWeaponItem::CSubWeaponItem()
{
    subWeaponType = -1;

    ay = DEFAULT_GRAVITY;

    animation_set = CAnimationSets::GetInstance()->Get(SUBWEAPONITEM_ANI_SET_ID);

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

void CSubWeaponItem::LoadExtraSetting(vector<int> extra_settings)
{
    if (extra_settings.size() > 0)
        this->subWeaponType = extra_settings[0];
    this->SetWeaponItem();
}