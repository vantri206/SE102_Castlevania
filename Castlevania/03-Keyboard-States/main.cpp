#pragma one
#include <windows.h>

#include "debug.h"
#include "Game.h"

#include "Animation.h"
#include "Animations.h"
#include "Sprite.h"
#include "Sprites.h"
#include "GameObject.h"
#include "PlayScene.h"
#include "Map.h"
#include "SampleKeyEventHandler.h"
#include "Utils.h"
#include "Camera.h"
#include "GameDefine.h"
#include "Audio/SoundManager.h"

CSampleKeyHandler* keyHandler;

CScene* scene = NULL;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadResources()
{
	CGame::GetInstance()->LoadResources();

	//Load Sound
	SoundManager& soundMgr = SoundManager::GetInstance();
	soundMgr.Init();
		// Load music
	soundMgr.LoadSound("stage_1_bgm", L"resource/Sounds/Musics/Stage_01_Vampire_Killer.wav");
	soundMgr.LoadSound("game_start", L"resource/Sounds/Musics/Game_Start_Prologue.wav");
	soundMgr.LoadSound("game_over", L"resource/Sounds/Musics/Game_Over.wav"); 
	soundMgr.LoadSound("boss_battle", L"resource/Sounds/Musics/Boss_Battle_Poison_Mind.wav");

	// Load sound effects
	soundMgr.LoadSound("being_hit", L"resource/Sounds/SoundEffects/Being_Hit.wav");
	soundMgr.LoadSound("fishman_launching", L"resource/Sounds/SoundEffects/Fishman_Launching.wav");
	soundMgr.LoadSound("getting_heartbonus", L"resource/Sounds/SoundEffects/Getting_Heart_Bonus.wav");
	soundMgr.LoadSound("getting_heart", L"resource/Sounds/SoundEffects/Getting_Heart.wav");
	soundMgr.LoadSound("holy_cross", L"resource/Sounds/SoundEffects/Getting_Holy_Cross.wav");
	soundMgr.LoadSound("money_get", L"resource/Sounds/SoundEffects/Getting_Money_Bag.wav");
	soundMgr.LoadSound("powerup", L"resource/Sounds/SoundEffects/Getting_Powerup.wav");
	soundMgr.LoadSound("time_bonus", L"resource/Sounds/SoundEffects/Getting_Time_Bonus.wav");
	soundMgr.LoadSound("goto_castle", L"resource/Sounds/SoundEffects/Going_To_Castle.wav");
	soundMgr.LoadSound("money_hidden", L"resource/Sounds/SoundEffects/Hidden_Money_Bag_Found.wav");
	soundMgr.LoadSound("hit_block", L"resource/Sounds/SoundEffects/Hitting_Breakable_Block.wav");
	soundMgr.LoadSound("hit_st", L"resource/Sounds/SoundEffects/Hitting_Something.wav");
	soundMgr.LoadSound("hit_water", L"resource/Sounds/SoundEffects/Hitting_Water_Surface.wav");
	soundMgr.LoadSound("holy_water", L"resource/Sounds/SoundEffects/Holy_Water_Touching_Ground.wav");
	soundMgr.LoadSound("invisible_end", L"resource/Sounds/SoundEffects/Invisible_End.wav");
	soundMgr.LoadSound("invisible_start", L"resource/Sounds/SoundEffects/Invisible_Start.wav");
	soundMgr.LoadSound("landing", L"resource/Sounds/SoundEffects/Landing.wav");
	soundMgr.LoadSound("life_lost", L"resource/Sounds/SoundEffects/Live_Lost_.wav");
	soundMgr.LoadSound("stage_clear", L"resource/Sounds/SoundEffects/Stage_Clear_.wav");
	soundMgr.LoadSound("stopwatch", L"resource/Sounds/SoundEffects/Stopwatch_Start.wav");
	soundMgr.LoadSound("throw_dagger", L"resource/Sounds/SoundEffects/Throwing_Dagger.wav");
	soundMgr.LoadSound("timeout", L"resource/Sounds/SoundEffects/Timeout_Warning.wav");
	soundMgr.LoadSound("use_door", L"resource/Sounds/SoundEffects/Using_Door.wav");
	soundMgr.LoadSound("use_wp", L"resource/Sounds/SoundEffects/Using_Weapon.wav");


	CGame* game = CGame::GetInstance();
	game->LoadScene(SCENE2, 2, STAGE2_FILE_PATH, STAGE2_OBJECT_FILE_PATH);
	game->ChangeScene(2);
}

void Update(DWORD dt)
{
	CGame* game = CGame::GetInstance();
	game->GetCurrentScene()->Update(dt);
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	UINT slot = 0;

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	ID3D10SamplerState* pointSampler = g->GetPointSampler();
	pD3DDevice->PSSetSamplers(slot, 1, &pointSampler);

	g->GetCurrentScene()->Render();

	spriteHandler->End();
	pSwapChain->Present(0, 0);

}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			CGame::GetInstance()->ProcessKeyboard();
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDebugWindow(hWnd);

	CGame* game = CGame::GetInstance();
	game->Init(hWnd, hInstance);
	game->InitKeyboard();
	game->Init(hWnd, hInstance);

	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}