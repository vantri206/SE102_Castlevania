#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "Scene.h"

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
protected:
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

	int mapWidth;
	int mapHeight;
	int mapId;
public:

	void Init(HWND hWnd,HINSTANCE hInstance);

	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b)
	{
		this->Draw(x, y, 1, tex, l, t, r, b, 1.0f);
	}
	void Draw(float x, float y, int nx, LPTEXTURE tex, int l, int t, int r, int b)
	{
		this->Draw(x, y, nx, tex, l, t, r, b, 1.0f);
	}
	void Draw(float x, float y, int nx, LPTEXTURE tex, int l, int t, int r, int b, float size);

	LPD3DX10SPRITE GetSpriteHandler() { return this->spriteHandler; }

	// Keyboard related functions 
	void InitKeyboard();
	int IsKeyDown(int KeyCode);
	int IsKeyUp(int KeyCode);
	void ProcessKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }

	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void LoadResources();
	ID3D10Device* GetDirect3DDevice() {
		return pD3DDevice;
	}


	LPTEXTURE LoadTexture(LPCWSTR texturePath);

	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }


	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }

	void SetCurrentMap(int _mapId, int _mapWidth, int _mapHeight)
	{
		this->mapId = _mapId;
		this->mapHeight = _mapHeight;
		this->mapWidth = _mapWidth;
	}
	int GetCurrentMapWidth() { return this->mapWidth; }
	int GetCurrentMapHeight() { return this->mapHeight; }
	int GetCurrentMapId() { return this->mapId; }

	static CGame* GetInstance();

	~CGame();
};