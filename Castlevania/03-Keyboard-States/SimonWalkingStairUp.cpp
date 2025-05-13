#include "SimonWalkingStairUp.h"
#include "SimonStairUpIdle.h"
#include "Simon.h"
#include "Stair.h"

CSimonWalkingStairUp::CSimonWalkingStairUp(CSimon* simon) 
{
	int dir_x = simon->GetDirectionX(), dir_y = simon->GetDirectionY();
	simon->SetAniId(ID_ANI_SIMON_GO_UP);
	simon->SetSpeed(SIMON_WALKING_STAIR_SPEED * dir_x, SIMON_WALKING_STAIR_SPEED * dir_y);
	simon->SetAccel(0.0f, 0.0f);
}
void CSimonWalkingStairUp::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonWalkingStairUp::KeyUpHandle(CSimon* simon, int keyCode) 
{
	if (keyCode == DIK_UP)
	{
		simon->SetState(new CSimonStairUpIdle(simon));
	}
}
void CSimonWalkingStairUp::Update(CSimon* simon, DWORD dt)
{
	if (simon->GetNearbyStair() != nullptr)
	{
		float l, t, r, b;
		simon->GetBoundingBox(l, t, r, b);
		CStair* stair = simon->GetNearbyStair();
		if (b >= stair->GetY() && stair->GetStairDirection() == DOWN_STAIR_DIRECTION)
		{
			simon->SetState(new CSimonIdle(simon));
		}
	}
}
void CSimonWalkingStairUp::OnNoCollision(CSimon* simon, DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonWalkingStairUp::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{

}