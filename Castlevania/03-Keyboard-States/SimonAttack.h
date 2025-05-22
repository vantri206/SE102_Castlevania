#pragma once
#include "SimonState.h"
#include "Whip.h"

#define SIMON_ATTACK_TIME 450

class CSimonAttack : public CSimonState {
private:
    ULONGLONG attackStartTime;
    CWhip* whip;
public:
    CSimonAttack(CSimon* simon);
    ~CSimonAttack();
    void KeyDownHandle(CSimon* simon, int keyCode);
    void KeyUpHandle(CSimon* simon, int keyCode);
    void Update(CSimon* simon, DWORD dt);
    void OnNoCollision(CSimon* simon, DWORD dt);
    void OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e);
    void Render();
};
