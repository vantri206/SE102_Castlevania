#pragma once
#include "GameObject.h"

class CTriggerZone : public CGameObject
{
protected:
    float width, height;
    float spawnX, spawnY;
    int spawnObjectId;
    int isSpawnObjectHidden;
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