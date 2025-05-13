#pragma once
#include <algorithm>
#include "Simon.h"
#include "Camera.h"
#include "Enemy.h"
#include "Brick.h"
#include "Candle.h"
#include "Whip.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, dt, coObjects);

	this->CheckStairNearby(coObjects);

	currentState->Update(this, dt);
	int mapwidth = CGame::GetInstance()->GetCurrentMapWidth();
	int mapheight = CGame::GetInstance()->GetCurrentMapHeight();

	vx += ax * dt;
	vy += ay * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	if (GetTickCount64() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (x <= 0 || x >= mapwidth - SIMON_WIDTH)
	{
		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= mapwidth - SIMON_WIDTH)
		{
			x = (float)(mapwidth - SIMON_WIDTH);
		}
	}
	CCamera::GetInstance()->Update(dt, this, mapwidth, mapheight);
}
void CSimon::OnNoCollision(DWORD dt)
{
	currentState->OnNoCollision(this, dt);
}
void CSimon::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CSimon*>(e->obj)) return;
	currentState->OnCollisionWith(this, e);
}
void CSimon::UpdateMoving(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CSimon::OnKeyDown(int keyCode)
{
	currentState->KeyDownHandle(this, keyCode);
}

void CSimon::OnKeyUp(int keyCode)
{
	currentState->KeyUpHandle(this, keyCode);
}

void CSimon::SetState(CSimonState* state) 
{
	currentState.reset(state);
}

int CSimon::CanCollisionWithObj(LPGAMEOBJECT objDests)
{
	if (dynamic_cast<CBrick*>(objDests) && this->isOnStair == true)
		return 0;
	return 1;
}

CSimonState* CSimon::GetState()
{
	return currentState.get();
}

void CSimon::Render()
{
	animation_set->at(ani_id)->Render(x, y, nx, SIMON_SIZE);
	currentState->Render(this);
}

void CSimon::CheckStairNearby(vector<LPGAMEOBJECT>* coObjects)
{
	this->nearbyStair = nullptr;
	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);
	for (size_t i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CStair*>(coObjects->at(i)))
		{
			CStair* stair = dynamic_cast<CStair*>(coObjects->at(i));
			float l1, t1, r1, b1;
			stair->GetBoundingBox(l1, t1, r1, b1);
			if (min(r, r1) >= max(l, l1) && min(t, t1) >= max(b, b1))
			{
				this->nearbyStair = stair;
			}
		}
	}
}
bool CSimon::IsNearStairUp()
{
	if (nearbyStair != nullptr)
	{
		if (nearbyStair->GetStairDirection() == UP_STAIR_DIRECTION)
		{
			return true;
		}
	}
	return false;
}
bool CSimon::IsNearStairDown()
{
	if (nearbyStair != nullptr)
	{
		if (nearbyStair->GetStairDirection() == DOWN_STAIR_DIRECTION)
		{
			return true;
		}
	}
	return false;
}

