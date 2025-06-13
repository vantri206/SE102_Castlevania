#pragma once
#include "GameObject.h"

#define TRIGGER_ZONE_ITEM 0
#define TRIGGER_ZONE_ENEMY 1

class CTriggerZone : public CGameObject
{
protected:
    int typeTriggerZone;
    float spawnX, spawnY;
    int spawnObjectId;
    int isSpawnObjectHidden;
    int enemyTriggerId;
    vector<int> spawnObjectExtraSettings;
public:
    CTriggerZone();
    void Render() {}
    void Update(DWORD dt, vector<LPGAMEOBJECT*>* coObjects) {}
    void Trigger();

    int IsOverlappable() { return 1; }
    int IsBlocking() { return 0; }
    
    void LoadExtraSetting(vector<int> extra_settings);
};