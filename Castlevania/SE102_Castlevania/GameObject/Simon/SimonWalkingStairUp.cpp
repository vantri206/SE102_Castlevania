#include "SimonWalkingStairUp.h"
#include "SimonStairUpIdle.h"
#include "Simon.h"
#include "Stair.h"

CSimonWalkingStairUp::CSimonWalkingStairUp(CSimon* simon, int isFirstEntry) : CSimonState(simon)
{
	int dir_x = simon->GetDirectionX(), dir_y = simon->GetDirectionY();
	simon->SetAniId(ID_ANI_SIMON_GO_UP);
	simon->SetSpeed(SIMON_WALKING_STAIR_SPEED * dir_x, SIMON_WALKING_STAIR_SPEED * dir_y);
	simon->SetAccel(0.0f, 0.0f);
	
	if (isFirstEntry) simon->UpdateMoving(SIMON_TIME_FIRST_STEP_ONSTAIR);
}
void CSimonWalkingStairUp::KeyDownHandle(int keyCode) {}
void CSimonWalkingStairUp::KeyUpHandle(int keyCode) 
{
	if (keyCode == DIK_UP)
	{
		simon->SetState(new CSimonStairUpIdle(simon));
	}
}
void CSimonWalkingStairUp::Update(DWORD dt)
{
	if (simon->GetNearbyStair() != nullptr)
	{
		float l, t, r, b;
		float sl, st, sr, sb;
		simon->GetBoundingBox(l, t, r, b);
		CStair* stair = simon->GetNearbyStair();
		stair->GetBoundingBox(sl, st, sr, sb);
		if (b >= sb && stair->GetStairDirection() == DOWN_STAIR_DIRECTION)
		{
			simon->SetState(new CSimonIdle(simon));
		}
	}
}
void CSimonWalkingStairUp::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonWalkingStairUp::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		simon->OnCollisionWithEnemyOnStair(enemy);
	}
}