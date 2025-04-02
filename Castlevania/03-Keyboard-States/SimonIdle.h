#pragma once

#include "SimonState.h"

class CSimonIdle : public CSimonState
{
public:
    virtual void KeyUpHandle(CSimon* simon, int keyCode) override;
    virtual void KeyDownHandle(CSimon* simon, int keyCode) override;
    virtual void Update(CSimon* simon) override;
};