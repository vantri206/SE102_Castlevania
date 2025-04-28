#pragma once
#include "SimonState.h"

class CSimonHurt : public CSimonState
{
    DWORD startHurtTime = GetTickCount64();
    bool finishedHurt=false; 

public:
    void KeyUpHandle(CSimon* simon, int keyCode) override;
    void KeyDownHandle(CSimon* simon, int keyCode) override;
    void Update(CSimon* simon) override;
};
