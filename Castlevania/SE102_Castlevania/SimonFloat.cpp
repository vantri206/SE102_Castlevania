#include "SimonFloat.h"
#include "Simon.h"
#include "SimonFalling.h"
#include "GameDefine.h"
#include "SimonAttack.h"

CSimonFloat::CSimonFloat(CSimon* simon) : CSimonState(simon)
{
	float vx, vy, ax, ay;
	simon->GetPhysical(vx, vy, ax, ay);
	simon->SetSize(SIMON_SIT_WIDTH, SIMON_SIT_HEIGHT);
	simon->SetAniId(ID_ANI_SIMON_SIT);

	floatStart = GetTickCount64();
}

void CSimonFloat::Update(DWORD dt)
{
	float vx, vy, ax, ay;
	simon->GetPhysical(vx, vy, ax, ay);
	if (vy<0.0f)
	{
		simon->SetPosition(simon->GetX(), simon->GetY() - (SIMON_IDLE_HEIGHT - SIMON_SIT_HEIGHT) / 2);
		simon->SetState(new CSimonFalling(simon));
	}
}
void CSimonFloat::KeyDownHandle(int keyCode) {
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
void CSimonFloat::KeyUpHandle(int keyCode){}
void CSimonFloat::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}

void CSimonFloat::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		simon->SetPosition(simon->GetX(), simon->GetY() + (SIMON_HURT_HEIGHT - SIMON_SIT_HEIGHT) / 2);
		simon->SetState(new CSimonHurt(simon));
	}
	else if (e->ny > 0 && e->obj->IsBlocking())
	{
		simon->SetPosition(simon->GetX(), simon->GetY() + (SIMON_IDLE_HEIGHT - SIMON_SIT_HEIGHT) / 2);
		simon->SetState(new CSimonIdle(simon));
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		simon->SetVx(0.0f);
	}
}