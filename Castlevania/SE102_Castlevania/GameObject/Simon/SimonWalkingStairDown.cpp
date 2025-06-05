#include "SimonWalkingStairDown.h"
#include "SimonStairDownIdle.h"
#include "Simon.h"
#include "Stair.h"
#include "SimonSit.h"

CSimonWalkingStairDown::CSimonWalkingStairDown(CSimon* simon) : CSimonState(simon)
{
	int dir_x = simon->GetDirectionX(), dir_y = simon->GetDirectionY();
	simon->SetAniId(ID_ANI_SIMON_GO_DOWN);
	simon->SetSpeed(SIMON_WALKING_STAIR_SPEED * dir_x, SIMON_WALKING_STAIR_SPEED * (-1) * dir_y);
	simon->SetAccel(0.0f, 0.0f);
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
	if (simon->GetNearbyStair() != nullptr)
	{
		float l, t, r, b;
		simon->GetBoundingBox(l, t, r, b);
		CStair* stair = simon->GetNearbyStair();
		if (b <= stair->GetY() && stair->GetStairDirection() == UP_STAIR_DIRECTION)
		{
			simon->SetState(new CSimonSit(simon));
		}
	}
}
void CSimonWalkingStairDown::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonWalkingStairDown::OnCollisionWith(LPCOLLISIONEVENT e)
{

}