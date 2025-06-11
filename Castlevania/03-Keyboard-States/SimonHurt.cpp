#include "Simon.h"
#include "SimonIdle.h"
#include "SimonState.h"
#include "SimonHurt.h"

CSimonHurt::CSimonHurt(CSimon* simon)
{
	simon->SetAniId(ID_ANI_SIMON_HURT);
	int nx = simon->GetDirectionX();
	simon->SetPhysical(SIMON_HURT_VX * (-1) * nx, SIMON_HURT_VY, 0, GRAVITY);
	startHurtTime = GetTickCount64();
}
void CSimonHurt::KeyUpHandle(CSimon* simon, int keyCode) { }
void CSimonHurt::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonHurt::Update(CSimon* simon, DWORD dt)
{
	DWORD now = GetTickCount64();
	if (now - startHurtTime > SIMON_HURT_TIME)
		simon->SetState(new CSimonIdle(simon));
}
void CSimonHurt::OnNoCollision(CSimon* simon, DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonHurt::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
	if ((e->ny > 0 || e->nx != 0) && e->obj->IsBlocking())
	{
		simon->SetState(new CSimonIdle(simon));
	}
}