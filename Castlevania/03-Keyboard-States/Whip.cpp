#include "Whip.h"
#include "Game.h"

void CWhip::Update(DWORD dt) {
    if (!isActive) return;

    // Đồng bộ vị trí với Simon
    // Nếu Simon quay phải (nx > 0), cây roi xuất hiện bên phải Simon
    // Nếu Simon quay trái (nx < 0), cây roi xuất hiện bên trái Simon
    x = simon->GetX() + (simon->GetDirectionX() > 0 ? SIMON_WIDTH : -SIMON_WIDTH);
    y = simon->GetY();
    nx = simon->GetDirectionX();
}

void CWhip::Render() {
    if (!isActive) return;
    if (animation_set == nullptr) {
        DebugOut(L"[ERROR] Whip animation set is null!\n");
        return;
    }
    animation_set->at(ID_ANI_WHIP)->Render(x, y, nx, 0.5f);
}

void CWhip::SetState(int state) {
    CGameObject::SetState(state);
    switch (state) {
        case WHIP_STATE_ACTIVE:
            isActive = true;
            break;
        case WHIP_STATE_INACTIVE:
            isActive = false;
            break;
    }
}

void CWhip::Activate() {
    SetState(WHIP_STATE_ACTIVE);
}

void CWhip::Deactivate() {
    SetState(WHIP_STATE_INACTIVE);
}