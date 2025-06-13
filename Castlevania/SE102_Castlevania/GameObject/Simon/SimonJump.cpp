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
#define SIMON_FLOATING_CHANGE_SPEED 0.7f
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
		if (CGame::GetInstance()->IsKeyDown(DIK_UP))
		{
			if (simon->CanUseSubWeapon())
				simon->SetState(new CSimonAttack(simon, SUB_WEAPON));
		}
		else simon->SetState(new CSimonAttack(simon, PRIMARY_WEAPON));
	}
}
void CSimonJump::KeyUpHandle(int keyCode)
{
}
void CSimonJump::Update(DWORD dt)
{
	float vx, vy, ax, ay;
	simon->GetPhysical(vx, vy, ax, ay);
	DebugOut(L"vy= %f\n", vy);
	if (vy <= SIMON_FLOATING_CHANGE_SPEED)
	{
		DebugOut(L"vy2= %f\n", vy);
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
