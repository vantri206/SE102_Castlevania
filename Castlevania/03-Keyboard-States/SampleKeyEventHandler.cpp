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
		simon->SetState(SIMON_STATE_WALK);
		if (game->IsKeyDown(DIK_RIGHT)) simon->SetDirection(1);
		else simon->SetDirection(-1);

	}
	else if (game->IsKeyDown(DIK_UP) || game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_STATE_WALK_UP);
		if (game->IsKeyDown(DIK_UP)) simon->SetDirectionY(1);
		else simon->SetDirectionY(-1);
	}
	else if (game->IsKeyDown(DIK_A))
	{
		simon->SetState(SIMON_STATE_ATTACK);
	}
	else
		simon->SetState(SIMON_STATE_IDLE);
}