#pragma once
#include "GameObject.h"
#include "Candle.h"

class CTriggerZone : public CGameObject
{
public:
    CTriggerZone();
    void Render() {}
    void Update(DWORD dt) {}
    int IsOverlappable() { return 1; }
    int IsBlocking() { return 0; }
};
