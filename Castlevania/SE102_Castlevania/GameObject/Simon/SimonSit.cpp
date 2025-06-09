#include "SimonSit.h"
#include "SimonIdle.h"
#include "Simon.h"
#include "SimonSitAttack.h"

#define SIMON_SIT_WIDTH 16
#define SIMON_SIT_HEIGHT 24

CSimonSit::CSimonSit(CSimon* simon) : CSimonState(simon)
{
	simon->SetSpeed(0.0f, 0.0f);
	simon->SetAccel(0.0f, DEFAULT_GRAVITY);
	simon->SetAniId(ID_ANI_SIMON_SIT);
	simon->SetSize(SIMON_SIT_WIDTH, SIMON_SIT_HEIGHT);
}

void CSimonSit::KeyDownHandle(int keyCode)
{
	if (keyCode == DIK_A)
	{
		if (CGame::GetInstance()->IsKeyDown(DIK_UP))
		{
			if (simon->CanUseSubWeapon())
				simon->SetState(new CSimonSitAttack(simon, SUB_WEAPON));
		}
		else simon->SetState(new CSimonSitAttack(simon, PRIMARY_WEAPON));
	}
}
void CSimonSit::KeyUpHandle(int keyCode)
{
    if (keyCode == DIK_S)
    {
		simon->SetPosition(simon->GetX(), simon->GetY() + 4.0f);
        simon->SetState(new CSimonIdle(simon));
    }

}
void CSimonSit::Update(DWORD dt)
{

}

void CSimonSit::OnNoCollision(DWORD dt)
{
	
}

void CSimonSit::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		simon->OnCollisionWithEnemy(enemy);
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
