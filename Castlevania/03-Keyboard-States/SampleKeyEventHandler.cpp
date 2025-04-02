#pragma once
#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "Simon.h"

extern CSimon* simon;

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
        if (game->IsKeyDown(i))
        {
            simon->OnKeyDown(i);
        }
        if (game->IsKeyUp(i))
        {
            simon->OnKeyUp(i);
        }
    }
}
