#include <algorithm>
#include "debug.h"

#include "Simon.h"


void CSimon::Update(DWORD dt)
{
	x += vx * dt;
	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();

	if (x <= 0 || x >= BackBufferWidth - SIMON_WIDTH) {
		vx = -vx;
		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - SIMON_WIDTH)
		{
			x = (float)(BackBufferWidth - SIMON_WIDTH);
		}
		nx = -nx;
	}

}
void CSimon::Render()
{
	animation_set->at(this->GetAniId(state))->Render(x, y, nx);
}

void CSimon::SetState(int state)
{
	switch (state)
	{
		case SIMON_STATE_IDLE:
		{
			this->SimonIdle();
			break;
		}
		case SIMON_STATE_WALK:
		{
			this->SimonWalk();
			break;
		}
		case SIMON_STATE_ATTACK:
		{
			this->SimonAttack();
			break;
		}
		case SIMON_STATE_SIT:
		{
			this->SimonSit();
			break;
		}
	}
	CGameObject::SetState(state);
}

int CSimon::GetState()
{
	return this->state;
}

int CSimon::GetAniId(int state)
{
	switch (state)
	{
		case SIMON_STATE_IDLE:
		{
			return ID_ANI_SIMON_IDLE;
			break;
		}
		case SIMON_STATE_WALK:
		{
			return ID_ANI_SIMON_WALK;
			break;
		}
		case SIMON_STATE_ATTACK:
		{
			return ID_ANI_SIMON_ATTACK;
			break;
		}
		case SIMON_STATE_SIT:
		{
			return ID_ANI_SIMON_SIT;
			break;
		}
	}
}

void CSimon::SimonWalk()
{
	if (nx > 0) vx = SIMON_WALKING_SPEED;
	else vx = -SIMON_WALKING_SPEED;
}

void CSimon::SimonAttack()
{

}

void CSimon::SimonIdle()
{
	vx = 0;
}

void CSimon::SimonSit()
{
	vx = 0;
}
void GetBoundingBox()
{

}