#include "SimonWalkingStairs.h"
#include "Stairs.h"
#include "Simon.h"

CSimonWalkingStairs::CSimonWalkingStairs(CSimon* simon) {

}
void CSimonWalkingStairs::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonWalkingStairs::KeyUpHandle(CSimon* simon, int keyCode) {
	if (keyCode == DIK_UP && simon->GetDirectionX() > 0)
	{
		simon->SetState(new CSimonIdle(simon));
	}
	else if (keyCode == DIK_DOWN && simon->GetDirectionX() < 0)
	{
		simon->SetState(new CSimonIdle(simon));
	}
}
void CSimonWalkingStairs::Update(CSimon* simon, DWORD dt){}
void CSimonWalkingStairs::OnNoCollision(CSimon* simon, DWORD dt){ }
void CSimonWalkingStairs::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e){}