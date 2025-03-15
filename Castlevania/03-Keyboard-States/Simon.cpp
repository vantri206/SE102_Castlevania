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
	}
}
void CSimon::Render()
{
	int aniId = -1;

	if (state == SIMON_STATE_IDLE)
	{
		aniId = ID_ANI_SIMON_IDLE;
	}
	else if (state == SIMON_STATE_WALK)
	{
		aniId = ID_ANI_SIMON_WALK;
	}
	animation_set->at(aniId)->Render(x, y, nx);
}

void CSimon::SetState(int state)
{
	switch (state)
	{
		case SIMON_STATE_IDLE:
		{
			vx = 0;
			break;
		}
		case SIMON_STATE_WALK:
		{
			if (nx > 0) vx = SIMON_WALKING_SPEED;
			else vx = -SIMON_WALKING_SPEED;
			break;
		}
	}
	CGameObject::SetState(state);
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	return;
}