#include <algorithm>
#include "debug.h"

#include "Simon.h"


void CSimon::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();

	if (x <= 0 || x >= BackBufferWidth - SIMON_WIDTH) {
		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - SIMON_WIDTH)
		{
			x = (float)(BackBufferWidth - SIMON_WIDTH);
		}
	}

	if (y <= 0 || y >= BackBufferHeight - SIMON_HEIGHT) {
		if (y <= 0)
		{
			y = 0;
		}
		else if (y >= BackBufferHeight - SIMON_HEIGHT)
		{
			y = (float)(BackBufferHeight - SIMON_HEIGHT);
		}
	}
}
void CSimon::Render()
{
	animation_set->at(ani_id)->Render(x, y, nx);
}

void CSimon::SetState(int state)
{
	switch (state)
	{
		case SIMON_STATE_IDLE:
		{
			this->SimonIdle();
			ani_id = ID_ANI_SIMON_IDLE;
			break;
		}
		case SIMON_STATE_WALK:
		{
			this->SimonWalk();
			ani_id = ID_ANI_SIMON_WALK;
			break;
		}
		case SIMON_STATE_ATTACK:
		{
			this->SimonAttack();
			ani_id = ID_ANI_SIMON_ATTACK;
			break;
		}
		case SIMON_STATE_WALK_UP:
		{
			this->SimonWalkUp();
			ani_id = ID_ANI_SIMON_WALK_UP;
			break;
		}
	}
	CGameObject::SetState(state);
}

int CSimon::GetState()
{
	return this->state;
}

void CSimon::SimonWalkUp()
{
	vx = 0;
	if (ny > 0) vy = -SIMON_WALKING_SPEED;
	else vy = SIMON_WALKING_SPEED;
}

void CSimon::SimonWalk()
{
	vy = 0;
	if (nx > 0) vx = SIMON_WALKING_SPEED;
	else vx = -SIMON_WALKING_SPEED;
}

void CSimon::SimonAttack()
{
	vx = 0;
	vy = 0;
}

void CSimon::SimonIdle()
{
	vx = 0;
	vy = 0;
}

void CSimon::SimonSit()
{
	vx = 0;
	vy = 0;
}
void GetBoundingBox()
{

}
