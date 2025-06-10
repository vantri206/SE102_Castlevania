#include "SimonFalling.h"
#include "SimonIdle.h"
#include "debug.h"
#include "Game.h"
#include "Simon.h"
#include "SimonSit.h"

#define SIMON_FALLING_WIDTH 16
#define SIMON_FALLING_HEIGHT 24

CSimonFalling::CSimonFalling(CSimon* simon) : CSimonState(simon)
{
	simon->SetAniId(ID_ANI_SIMON_JUMP);
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
	/*
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		simon->SetState(new CSimonHurt(simon));
	}
	*/
	if (e->ny > 0 && e->obj->IsBlocking())
	{
		simon->SetState(new CSimonSit(simon));
	}
}
