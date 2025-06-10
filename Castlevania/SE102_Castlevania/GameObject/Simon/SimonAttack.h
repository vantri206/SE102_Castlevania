#pragma once
#include "SimonState.h"
#include "Whip.h"
#include "Weapon.h"

class CSimonAttack : public CSimonState {
private:
    ULONGLONG attackStartTime;
public:
    CSimonAttack(CSimon* simon, int weaponType);
    ~CSimonAttack();
    void KeyDownHandle(int keyCode);
    void KeyUpHandle(int keyCode);
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    void Render();
};