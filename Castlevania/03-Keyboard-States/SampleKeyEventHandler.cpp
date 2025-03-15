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

	if (game->IsKeyDown(DIK_RIGHT))
	{
		simon->SetDirection(1);
		simon->SetState(SIMON_STATE_WALK);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		simon->SetDirection(-1);
		simon->SetState(SIMON_STATE_WALK);
	}
	else
		simon->SetState(SIMON_STATE_IDLE);
	
}