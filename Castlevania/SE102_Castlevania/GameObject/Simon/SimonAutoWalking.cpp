#pragma once

#include "Simon.h"
#include "SimonIntro.h"
#include "SimonAutoWalking.h"
#include "SimonStairUpIdle.h"
#include "SimonStairDownIdle.h"
#include "SimonWalkingStairUp.h"
#include "SimonWalkingStairDown.h"

#define AUTO_WALK_EPSILON 1.0f

CSimonAutoWalking::CSimonAutoWalking(CSimon* simon, float x, float y, int direction, int simonState) : CSimonState(simon)
{
	int moveDir = (x > simon->GetX()) ? NEGATIVE_DIRECTION : POSITIVE_DIRECTION;
	simon->SetDirectionX(moveDir);
	simon->SetVx(SIMON_AUTO_WALKING_STAIR_SPEED * moveDir);
	simon->SetAniId(ID_ANI_SIMON_WALK);
	simon->SetSize(SIMON_WALKING_WIDTH, SIMON_WALKING_HEIGHT);
	targetX = x;
	targetY = y;
	finishedDirection = direction;
	nextState = simonState;
}
void CSimonAutoWalking::Update(DWORD dt)
{
	if(CheckReachedTarget())
	{
		simon->SetSpeed(0.0f, 0.0f);
		simon->SetPosition(targetX, simon->GetY());
		simon->SetDirectionX(finishedDirection);
		ChangeState();
	}
}
void CSimonAutoWalking::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}
void CSimonAutoWalking::OnCollisionWith(LPCOLLISIONEVENT e)
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

bool CSimonAutoWalking::CheckReachedTarget()
{
	float x, y;
	simon->GetPosition(x, y);

	bool reachedX = abs(x - targetX) <= AUTO_WALK_EPSILON;
	bool reachedY = abs(y - targetY) <= AUTO_WALK_EPSILON;
	return (reachedX);
}

void CSimonAutoWalking::ChangeState()
{
	switch (nextState)
	{
	case SIMON_STATE_WALKING_UP:
		simon->SetState(new CSimonWalkingStairUp(simon));
		break;
	case SIMON_STATE_WALKING_DOWN:
		simon->SetState(new CSimonWalkingStairDown(simon));
		break;
	case SIMON_STATE_INTRO:
		simon->SetState(new CSimonIntro(simon));
		break;
	}
}