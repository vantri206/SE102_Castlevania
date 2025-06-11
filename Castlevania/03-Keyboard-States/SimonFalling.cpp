#include "SimonFalling.h"
#include "SimonIdle.h"
#include "debug.h"
#include "Game.h"
#include "Simon.h"
#include "SimonSit.h"
#include "Audio/SoundManager.h"


#define SIMON_FALLING_WIDTH 16
#define SIMON_FALLING_HEIGHT 24

CSimonFalling::CSimonFalling(CSimon* simon)
{
	simon->SetAniId(ID_ANI_SIMON_JUMP);
	simon->SetSize(SIMON_FALLING_WIDTH, SIMON_FALLING_HEIGHT);
}
void CSimonFalling::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonFalling::KeyUpHandle(CSimon* simon, int keyCode) {}
void CSimonFalling::Update(CSimon* simon, DWORD dt)
{

}
void CSimonFalling::OnNoCollision(CSimon* simon, DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonFalling::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
	/*
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		simon->SetState(new CSimonHurt(simon));
	}
	*/
	SoundManager::GetInstance().PlaySound("landing");
	if (e->ny > 0 && e->obj->IsBlocking())
	{	
		simon->SetState(new CSimonSit(simon));
	}
}

