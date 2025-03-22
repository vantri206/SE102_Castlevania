#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


#include "KeyEventHandler.h"
#include "d3dx9core.h"
#include "Texture.h"

#define MAX_FRAME_RATE 60
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256


/*
	Our simple game framework
*/
class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	LPD3DX10SPRITE spriteHandler = NULL;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state
	
	
	
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	HINSTANCE hInstance;

	int currentMapId = 1;
public:
	// Init DirectX, Sprite Handler
	void Init(HWND hWnd,HINSTANCE hInstance);

	//
	// Draw a portion or ALL the texture at position (x,y) on the screen
	// rect : if NULL, the whole texture will be drawn
	//        if NOT NULL, only draw that portion of the texture 
	void Draw(float x, float y, int nx, LPTEXTURE tex, int l, int t, int r, int b);

	LPD3DX10SPRITE GetSpriteHandler() { return this->spriteHandler; }

	// Keyboard related functions 
	void InitKeyboard(LPKEYEVENTHANDLER handler);
	int IsKeyDown(int KeyCode);
	int IsKeyUp(int KeyCode);
	void ProcessKeyboard();

	ID3D10Device* GetDirect3DDevice() {
		return pD3DDevice;
	}

	LPTEXTURE CGame::LoadTexture(LPCWSTR texturePath);

	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }


	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }

	int GetCurrentMap() { return currentMapId; }

	static CGame* GetInstance();

	~CGame();
};