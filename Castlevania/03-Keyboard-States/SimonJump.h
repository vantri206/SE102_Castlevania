#pragma once
#include "SimonState.h"

class CSimonJump : public CSimonState {
private:
	DWORD jumpStartTime;
public:
    CSimonJump(CSimon* simon);
    void KeyDownHandle(int keyCode);
    void KeyUpHandle(int keyCode);
    void Update(DWORD dt);
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
};
