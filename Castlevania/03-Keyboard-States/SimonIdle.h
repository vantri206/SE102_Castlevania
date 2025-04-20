#pragma once

#include "SimonState.h"

class CSimonIdle : public CSimonState
{
public:
    void KeyUpHandle(CSimon* simon, int keyCode) override;
    void KeyDownHandle(CSimon* simon, int keyCode) override;
    void Update(CSimon* simon) override;
};