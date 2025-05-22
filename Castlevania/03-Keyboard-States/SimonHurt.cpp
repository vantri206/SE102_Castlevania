
#include "Simon.h"
#include "SimonIdle.h"
#include "SimonState.h"
#include "SimonHurt.h"
CSimonHurt::CSimonHurt(CSimon* simon)
{
	
}
void CSimonHurt::KeyUpHandle(CSimon* simon, int keyCode) { }
void CSimonHurt::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonHurt::Update(CSimon* simon, DWORD dt)
{
	simon->SetState(new CSimonIdle());
}
void CSimonHurt::OnNoCollision(CSimon* simon, DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonHurt::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e) {}