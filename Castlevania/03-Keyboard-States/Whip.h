#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Simon.h"

#define WHIP_STATE_INACTIVE 0
#define WHIP_STATE_ACTIVE 1

#define ID_ANI_WHIP 1000  // ID animation cho cây roi

class CWhip : public CGameObject {
protected:
    CSimon* simon;  // Reference tới Simon
    bool isActive;

public:
    CWhip(CSimon* owner) : CGameObject(0, 0) {
        simon = owner;
        isActive = false;
        state = WHIP_STATE_INACTIVE;
    }

    void Update(DWORD dt) override;
    void Render() override;
    void SetState(int state) override;
    void Activate();
    void Deactivate();
};