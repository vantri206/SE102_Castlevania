#pragma once
#include "SimonState.h"

class CSimonSit : public CSimonState {
public:
    void KeyDownHandle(CSimon* simon, int keyCode) override;
    void KeyUpHandle(CSimon* simon, int keyCode) override;
    void Update(CSimon* simon) override;
};
