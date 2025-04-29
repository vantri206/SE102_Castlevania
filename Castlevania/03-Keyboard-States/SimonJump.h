#pragma once
#include "SimonState.h"

class CSimonJump : public CSimonState {
private:
    float vy;
    bool jumping;
	DWORD jumpStartTime;
public:
    CSimonJump();
    void KeyDownHandle(CSimon* simon, int keyCode) override;
    void KeyUpHandle(CSimon* simon, int keyCode) override;
    void Update(CSimon* simon) override;
};
