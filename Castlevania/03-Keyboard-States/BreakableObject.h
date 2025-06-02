#pragma once
#include "GameObject.h"

#define BREAKABLEOBJCET_DESTROYED_TIME 900

class CBreakableObject : public CGameObject
{
protected:
    int itemdropId;
    DWORD startDestroyedTime;
public:
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render() {}

    virtual void LoadExtraSetting(vector<int> extra_settings);

    virtual void OnHit();
    
    virtual void SetItemDrop(int itemid);
    virtual void TriggerDestroyedEffect(int duration);
};
