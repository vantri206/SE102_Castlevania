#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "Simon.h"
#include "PlayScene.h"


void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	CSimon* simon = CPlayScene::GetInstance()->getPlayer();
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = (CSimon*)(((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->getPlayer());
	if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
	{
		simon->SetState(SIMON_STATE_WALK);
		if (game->IsKeyDown(DIK_RIGHT)) simon->SetDirectionX(1);
		else simon->SetDirectionX(-1);

	}
	else if (game->IsKeyDown(DIK_UP) || game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_STATE_GO_UP);
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