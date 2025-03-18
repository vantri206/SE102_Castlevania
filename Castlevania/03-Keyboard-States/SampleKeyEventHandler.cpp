#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "Simon.h"


extern CSimon* simon;

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	CGame* game = CGame::GetInstance();

	if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
	{
		if (simon->GetState() != SIMON_STATE_SIT)
		{
			simon->SetState(SIMON_STATE_WALK);
		}
		if (game->IsKeyDown(DIK_RIGHT)) simon->SetDirection(1);
		else simon->SetDirection(-1);
	}
	else if (game->IsKeyDown(DIK_A))
	{
		simon->SetState(SIMON_STATE_ATTACK);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_STATE_SIT);
	}
	else
		simon->SetState(SIMON_STATE_IDLE);
	
}