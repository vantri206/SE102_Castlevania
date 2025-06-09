#pragma once
#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "Simon.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

}

void CSampleKeyHandler::KeyState(BYTE* states)
{
    CGame* game = CGame::GetInstance();

    for (int i = 0; i < KEYBOARD_STATE_SIZE; i++)
    {
        CSimon* player = nullptr;
        player = CSceneManager::GetInstance()->GetPlayer();
        if (!player) continue;
        if (game->IsKeyDown(i))
        {
            player->OnKeyDown(i);
        }
        if (game->IsKeyUp(i))
        {
            player->OnKeyUp(i);
        }
    }
}
