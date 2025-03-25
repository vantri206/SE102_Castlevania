#include "Whip.h"
#include "Game.h"

void CWhip::Update(DWORD dt) {
    // Đồng bộ vị trí với Simon
    x = simon->x + (simon->GetDirectionX() > 0 ? SIMON_WIDTH : -SIMON_WIDTH);
    y = simon->y;
    nx = simon->GetDirectionX();
}

void CWhip::Render() {
    if (animation_set == nullptr) {
        DebugOut(L"[ERROR] Whip animation set is null!\n");
        return;
    }
    animation_set->at(ID_ANI_WHIP)->Render(x, y, nx, 0.5f);
}