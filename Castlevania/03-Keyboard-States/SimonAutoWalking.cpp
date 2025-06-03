
#include "SimonAutoWalking.h"
#include "SimonStairUpIdle.h"
#include "SimonStairDownIdle.h"
#include "SimonIdle.h"
#include "Simon.h"
#include "debug.h"
#define SIMON_WALKING_WIDTH 15
#define SIMON_WALKING_HEIGHT 30
#define AUTO_WALK_EPSILON 2.0f

CSimonAutoWalking::CSimonAutoWalking(CSimon* simon, float x, int direction, AutoWalkPurpose purpose)
{
	this->targetX = x;
	this->stairDirection = direction;
	this->purpose = purpose;

	int moveDir = (x > simon->GetX()) ? 1 : -1;
	simon->SetDirectionX(moveDir);
	simon->SetMaxVx(SIMON_AUTOWALKING_SPEED * moveDir);
	simon->SetAccel(SIMON_ACCEL_WALK_X * moveDir, GRAVITY);
	simon->SetAniId(ID_ANI_SIMON_WALK);
	simon->SetSize(SIMON_WALKING_WIDTH, SIMON_WALKING_HEIGHT);
}

void CSimonAutoWalking::Update(CSimon* simon, DWORD dt)
{
	float x, y;
	simon->GetPosition(x, y);
	if (abs(x - targetX) <= AUTO_WALK_EPSILON)
	{
		simon->SetAccel(0.0f, GRAVITY);
		simon->SetSpeed(0.0f, 0.0f);

		switch (purpose)
		{
		case WALK_TO_STAIR_UP:
			simon->SetDirectionX(stairDirection);
			simon->SetState(new CSimonStairUpIdle(simon));
			break;

		case WALK_TO_STAIR_DOWN:
			simon->SetDirectionX(stairDirection);
			simon->SetState(new CSimonStairDownIdle(simon));
			break;
		default:
			simon->SetState(new CSimonIdle(simon));
			break;
		}
	}
}


void CSimonAutoWalking::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonAutoWalking::KeyUpHandle(CSimon* simon, int keyCode) {}
void CSimonAutoWalking::OnNoCollision(CSimon* simon, DWORD dt) {}
void CSimonAutoWalking::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e) {}
