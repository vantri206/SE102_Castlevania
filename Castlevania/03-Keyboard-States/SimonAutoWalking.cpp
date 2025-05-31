
#include "SimonAutoWalking.h"
#include "SimonStairUpIdle.h"
#include "SimonStairDownIdle.h"
#include "SimonIdle.h"
#include "Simon.h"
#include "debug.h"
#define SIMON_WALKING_WIDTH 15
#define SIMON_WALKING_HEIGHT 30
#define AUTO_WALK_EPSILON 2.0f

CSimonAutoWalking::CSimonAutoWalking(CSimon* simon, float x, int direction, bool isGoingUp)
{
	this->targetX = x;
	this->stairDirection = direction;
	this->goingUp = isGoingUp;

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
	DebugOut(L"Simon Auto Walking Stair: x = %f, targetX = %f, direction = %d, goingUp = %d\n", x, targetX, stairDirection, goingUp);
	if (abs(x - targetX) <= AUTO_WALK_EPSILON)
	{
		// Đã đến đúng vị trí cầu thang
		simon->SetAccel(0.0f, GRAVITY);
		simon->SetSpeed(0.0f, 0.0f);
		simon->SetDirectionX(stairDirection); // Hướng lên/xuống cầu thang

		if (goingUp)
			simon->SetState(new CSimonStairUpIdle(simon));
		else
			simon->SetState(new CSimonStairDownIdle(simon));
	}
}
void CSimonAutoWalking::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonAutoWalking::KeyUpHandle(CSimon* simon, int keyCode) {}
void CSimonAutoWalking::OnNoCollision(CSimon* simon, DWORD dt) {}
void CSimonAutoWalking::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e) {}
