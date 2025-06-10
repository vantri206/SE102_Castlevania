#pragma once
#include "SimonState.h"
#include "Whip.h"
#include "Weapon.h"

#define SIMON_ATTACK_TIME 500

class CSimonStairUpAttack : public CSimonState {
private:
    ULONGLONG attackStartTime;
public:
    CSimonStairUpAttack(CSimon* simon);
    ~CSimonStairUpAttack();
    void KeyDownHandle(int keyCode);
    void KeyUpHandle(int keyCode);
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    void Render();
};