#include "SimonWalkingStairDown.h"
#include "SimonStairDownIdle.h"
#include "Simon.h"
#include "Stair.h"

CSimonWalkingStairDown::CSimonWalkingStairDown(CSimon* simon)
{
	int dir_x = simon->GetDirectionX(), dir_y = simon->GetDirectionY();
	simon->SetAniId(ID_ANI_SIMON_GO_DOWN);
	simon->SetSpeed(SIMON_WALKING_STAIR_SPEED * dir_x, SIMON_WALKING_STAIR_SPEED * (-1) * dir_y);
	simon->SetAccel(0.0f, 0.0f);
}
void CSimonWalkingStairDown::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonWalkingStairDown::KeyUpHandle(CSimon* simon, int keyCode)
{
	if (keyCode == DIK_DOWN)
	{
		simon->SetState(new CSimonStairDownIdle(simon));
	}
}
void CSimonWalkingStairDown::Update(CSimon* simon, DWORD dt)
{
	if (simon->GetNearbyStair() != nullptr)
	{
		float l, t, r, b;
		simon->GetBoundingBox(l, t, r, b);
		CStair* stair = simon->GetNearbyStair();
		if (b <= stair->GetY() && stair->GetStairDirection() == UP_STAIR_DIRECTION)
		{
			simon->SetState(new CSimonIdle(simon));
		}
	}
}
void CSimonWalkingStairDown::OnNoCollision(CSimon* simon, DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonWalkingStairDown::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{

}