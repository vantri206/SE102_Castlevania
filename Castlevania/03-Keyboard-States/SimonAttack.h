#pragma once
#include "SimonState.h"
#include "Whip.h"
#include "Weapon.h"

#define SIMON_ATTACK_TIME 450

class CSimonAttack : public CSimonState {
private:
    ULONGLONG attackStartTime;
public:
    CSimonAttack(CSimon* simon);
    ~CSimonAttack();
    void KeyDownHandle(CSimon* simon, int keyCode);
    void KeyUpHandle(CSimon* simon, int keyCode);
    void Update(CSimon* simon, DWORD dt);
    void OnNoCollision(CSimon* simon, DWORD dt);
    void OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e);
    void Render(CSimon* simon);
};
