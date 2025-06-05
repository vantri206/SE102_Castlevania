#pragma once
#include "GameObject.h"

#define BREAKABLEOBJCET_DESTROYED_TIME 300

class CBreakableObject : public CGameObject
{
protected:
    int itemdropId;
    vector<int> itemDropExtraSettings;
    DWORD startDestroyedTime;
public:
    CBreakableObject()
    {
        itemdropId = -1;
        startDestroyedTime = -1;
        itemDropExtraSettings = vector<int>();
    }
    virtual void Update(DWORD dt, vector<CGameObject*>* coObjects);
    virtual void Render() {}

    virtual int IsOverlappable() { return 1; }

    virtual void LoadExtraSetting(vector<int> extra_settings);

    virtual void OnHit();
    
    virtual void SetItemDrop(int itemid);
    virtual void TriggerDestroyedEffect(int duration);
    virtual int isInDestroyed();
};
