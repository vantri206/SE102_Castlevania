#include "SimonWalkingStairDown.h"
#include "SimonStairDownIdle.h"
#include "Simon.h"
#include "Stair.h"
#include "SimonSit.h"
#include "SimonWalkingStairUp.h"
#include <Portal.h>

CSimonWalkingStairDown::CSimonWalkingStairDown(CSimon* simon) : CSimonState(simon)
{
	int dir_x = simon->GetDirectionX(), dir_y = simon->GetDirectionY();
	simon->SetAniId(ID_ANI_SIMON_GO_DOWN);
	simon->SetSpeed(SIMON_WALKING_STAIR_SPEED * dir_x, SIMON_WALKING_STAIR_SPEED * (-1) * dir_y);
	simon->SetAccel(0.0f, 0.0f);
	simon->SetOnStair(true);
}
void CSimonWalkingStairDown::KeyDownHandle(int keyCode) {}
void CSimonWalkingStairDown::KeyUpHandle(int keyCode)
{
	if (keyCode == DIK_DOWN)
	{
		simon->SetState(new CSimonStairDownIdle(simon));
	}
}
void CSimonWalkingStairDown::Update(DWORD dt)
{
	CStair* stair = simon->GetNearbyStair();
	if (stair)
	{
		float l, t, r, b;
		float sl, st, sr, sb;
		simon->GetBoundingBox(l, t, r, b);
		stair->GetBoundingBox(sl, st, sr, sb);
		if (b <= sb && stair->GetStairDirection() == UP_STAIR_DIRECTION)
		{
			simon->SetPosition(simon->GetX(), simon->GetY() + abs(sb - b));
			simon->SetOnStair(false);
			simon->SetState(new CSimonIdle(simon));
		}
	}
}
void CSimonWalkingStairDown::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonWalkingStairDown::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
    {
        CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
        simon->OnCollisionWithEnemyOnStair(enemy);
    }
	else if (dynamic_cast<CPortal*>(e->obj))
	{
		CPortal* portal = dynamic_cast<CPortal*>(e->obj);
		portal->ChangeScene();
	}
}