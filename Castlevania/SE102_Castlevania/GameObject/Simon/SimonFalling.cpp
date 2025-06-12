#include "SimonFalling.h"
#include "SimonIdle.h"
#include "debug.h"
#include "Game.h"
#include "Simon.h"
#include "SimonSit.h"
#include "TriggerZone.h"
#include "SimonDie.h"
#include "WaterDeadZone.h"

CSimonFalling::CSimonFalling(CSimon* simon) : CSimonState(simon)
{
	simon->SetAniId(ID_ANI_SIMON_SIT);
	simon->SetSize(SIMON_FALLING_WIDTH, SIMON_FALLING_HEIGHT);
}
void CSimonFalling::KeyDownHandle(int keyCode) {}
void CSimonFalling::KeyUpHandle(int keyCode) {}
void CSimonFalling::Update(DWORD dt)
{

}
void CSimonFalling::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonFalling::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		simon->SetState(new CSimonHurt(simon));
	}
	else if (dynamic_cast<CTriggerZone*>(e->obj))
	{
		CTriggerZone* triggerzone = dynamic_cast<CTriggerZone*>(e->obj);
		triggerzone->Trigger();
	}
	else if (dynamic_cast<CWaterDeadZone*>(e->obj))
	{
		float l, t, r, b;
		e->obj->GetBoundingBox(l, t, r, b);
		simon->TriggerSplashEffect(simon->GetX(), t);
		simon->StartDrowning();
	}
	else if (e->ny > 0 && e->obj->IsBlocking())
	{	
		simon->SetState(new CSimonSit(simon));
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		simon->SetVx(0.0f);
	}
}
