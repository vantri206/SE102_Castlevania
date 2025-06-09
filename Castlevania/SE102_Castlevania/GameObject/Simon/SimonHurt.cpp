#include "Simon.h"
#include "SimonIdle.h"
#include "SimonState.h"
#include "SimonHurt.h"
#include "SimonSit.h"

#define SIMON_HURT_WIDTH 16
#define SIMON_HURT_HEIGHT 28

CSimonHurt::CSimonHurt(CSimon* simon) : CSimonState(simon)
{
	simon->SetSize(SIMON_HURT_WIDTH, SIMON_HURT_HEIGHT);
	simon->SetAniId(ID_ANI_SIMON_HURT);
	int nx = simon->GetDirectionX();
	simon->SetPhysical(SIMON_HURT_VX * (-1) * nx, SIMON_HURT_VY, 0, DEFAULT_GRAVITY);
	startHurtTime = GetTickCount64();
}
void CSimonHurt::KeyUpHandle(int keyCode) { }
void CSimonHurt::KeyDownHandle(int keyCode) {}
void CSimonHurt::Update(DWORD dt)
{
	DWORD now = GetTickCount64();
	if (now - startHurtTime > SIMON_HURT_TIME)
		simon->SetState(new CSimonIdle(simon));
}
void CSimonHurt::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonHurt::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if ((e->ny != 0 || e->nx != 0) && e->obj->IsBlocking())
	{
		simon->SetState(new CSimonSit(simon));
	}
}