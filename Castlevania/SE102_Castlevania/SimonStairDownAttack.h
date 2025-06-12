#pragma once
#include "SimonState.h"
#include "Whip.h"
#include "Weapon.h"

#define SIMON_ATTACK_TIME 500

class CSimonStairDownAttack : public CSimonState {
private:
    ULONGLONG attackStartTime;
public:
    CSimonStairDownAttack(CSimon* simon);
    ~CSimonStairDownAttack();
    void KeyDownHandle(int keyCode);
    void KeyUpHandle(int keyCode);
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    void Render();
};