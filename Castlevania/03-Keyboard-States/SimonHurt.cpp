
#include "Simon.h"
#include "SimonIdle.h"
#include "SimonState.h"
#include "SimonHurt.h"
CSimonHurt::CSimonHurt(CSimon* simon)
{
	if(simon->GetUntouchable() == 0)
	{
		simon->SetMaxVx(SIMON_WALKING_SPEED * (-1) * simon->GetDirectionX());
		simon->SetAx(0);
		simon->SetVx(SIMON_WALKING_SPEED * (-1) * simon->GetDirectionX());
		simon->SetVy(BOUNCE_BACK_HEIGHT);
		simon->StartUntouchable();
		simon->SetAniId(ID_ANI_SIMON_HURT);
	}
}
void CSimonHurt::KeyUpHandle(CSimon* simon, int keyCode) { }
void CSimonHurt::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonHurt::Update(CSimon* simon, DWORD dt)
{
	simon->SetState(new CSimonIdle());
}
void CSimonHurt::OnNoCollision(CSimon* simon, DWORD dt)
{
	float vx, vy;
	simon->GetSpeed(vx, vy);
	DebugOut(L"Simon vx: %f\n", vx);
	simon->UpdateMoving(dt);
}
void CSimonHurt::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e) {}