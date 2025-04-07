#pragma once
#include "SimonState.h"

class CSimonAttack : public CSimonState {
private:
    DWORD attackStartTime = GetTickCount();
public:
    void KeyDownHandle(CSimon* simon, int keyCode) override;
    void KeyUpHandle(CSimon* simon, int keyCode) override;
    void Update(CSimon* simon) override;
};
