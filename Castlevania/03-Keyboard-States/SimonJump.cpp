//#include "SimonJump.h"
//#include "SimonIdle.h"
//#include "debug.h"
//#include "Game.h"
//#include "Simon.h"
//CSimonJump::CSimonJump() {
//    vy = -SIMON_JUMP_SPEED; 
//    jumping = true;
//}
//void CSimonJump::KeyDownHandle(CSimon* simon, int keyCode) {}
//void CSimonJump::KeyUpHandle(CSimon* simon, int keyCode) {}
//void CSimonJump::Update(CSimon* simon) {
//    vy += GRAVITY;
//    simon->SetVy(vy);
//    simon->SetAniId(ID_ANI_SIMON_JUMP);
//    /*if (simon->IsOnGround()) {
//        jumping = false;
//        simon->SetState(new CSimonIdle());
//    }*/
//    if (simon->GetY()==0) {
//        jumping = false;
//        simon->SetState(new CSimonIdle());
//    }
//}
//
