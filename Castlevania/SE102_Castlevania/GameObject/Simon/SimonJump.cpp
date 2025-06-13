#include "SimonJump.h"
#include "SimonIdle.h"
#include "debug.h"
#include "Game.h"
#include "SimonFloat.h"
#include "Simon.h"
#include "SimonSit.h"
#include "SimonFalling.h"
#include "SimonHurt.h"
#include "SimonAttack.h"

CSimonJump::CSimonJump(CSimon* simon) : CSimonState(simon)
{
	jumpStartTime = GetTickCount64();
	float vx, vy, ax, ay;
	simon->GetPhysical(vx, vy, ax, ay);
	simon->SetPhysical(vx, SIMON_JUMP_SPEED, ax, SIMON_GRAVITY_JUMP);
	simon->SetAniId(ID_ANI_SIMON_IDLE);
	simon->SetSize(SIMON_JUMP_WIDTH, SIMON_JUMP_HEIGHT);
}
void CSimonJump::KeyDownHandle(int keyCode)
{
	if (keyCode == DIK_A)
	{
		simon->SetState(new CSimonAttack(simon, PRIMARY_WEAPON));
	}
}
void CSimonJump::KeyUpHandle(int keyCode)
{
	if ((keyCode == DIK_RIGHT && simon->GetDirectionX() > 0) || (keyCode == DIK_LEFT && simon->GetDirectionX() < 0))
	{
		simon->SetAx(0.0f);
		simon->SetVx(0.0f);
	}
}
void CSimonJump::Update(DWORD dt)
{
	float vx, vy, ax, ay;
	simon->GetPhysical(vx, vy, ax, ay);
	if (vy <= 0.0f)	
	{
		simon->SetPosition(simon->GetX(), simon->GetY() + (SIMON_JUMP_HEIGHT - SIMON_SIT_HEIGHT) / 2);
		simon->SetState(new CSimonFloat(simon));
	}
}

void CSimonJump::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}

void CSimonJump::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		simon->OnCollisionWithEnemy(enemy);
	}
	else if (dynamic_cast<CItem*>(e->obj))
	{
		CItem* item = dynamic_cast<CItem*>(e->obj);
		simon->OnCollisionWithItem(item);
	}
	else if (e->ny > 0 && e->obj->IsBlocking())
	{
		simon->SetVy(0.0f);
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		simon->SetVx(0.0f);
	}
}
