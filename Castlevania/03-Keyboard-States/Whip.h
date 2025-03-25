#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Simon.h"

#define ID_ANI_WHIP 3000  // ID animation của cây roi từ resources.txt

class CWhip : public CGameObject {
protected:
    CSimon* simon;  // Reference tới Simon

public:
    CWhip(CSimon* owner) : CGameObject(0, 0) {
        simon = owner;
    }

    void Update(DWORD dt) override;
    void Render() override;  // Giữ lại để render khi cần
};