#include "SimonSit.h"
#include "SimonIdle.h"
#include "Simon.h"
void CSimonSit::KeyDownHandle(CSimon* simon, int keyCode) {
    if (keyCode == DIK_UP) {
        simon->SetState(new CSimonIdle());
    }
}
void CSimonSit::KeyUpHandle(CSimon* simon, int keyCode) {
    if (keyCode == DIK_DOWN) {
        simon->SetState(new CSimonIdle());
    }
}
void CSimonSit::Update(CSimon* simon) {
    simon->SetAniId(ID_ANI_SIMON_SIT);
}