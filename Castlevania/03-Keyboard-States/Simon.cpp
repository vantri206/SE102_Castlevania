#pragma once
#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Camera.h"
#include "Textures.h"

void CSimon::Update(DWORD dt)
{
	currentState->Update(this);

	int mapwidth = CGame::GetInstance()->GetCurrentMapWidth();
	int mapheight = CGame::GetInstance()->GetCurrentMapHeight();
	
	x += vx * dt;
	y += vy * dt;
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
	if(currentState != NULL) 
		delete currentState;
	currentState = state;
}

CSimonState* CSimon::GetState()
{
	return this->currentState;
}

void CSimon::Render()
{
	animation_set->at(ani_id)->Render(x, y, nx, SIMON_SIZE);
}


