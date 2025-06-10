#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include "Scene.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "KeyEventHandler.h"
#include "d3dx9core.h"
#include "Texture.h"
#include "GameDefine.h"

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

	ID3D10SamplerState* pPointSampler = nullptr;

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

	int currentSceneId = -1;
public:

	void Init(HWND hWnd, HINSTANCE hInstance);

	void DrawBoundingBox(float x, float y, float width, float height);

	LPD3DX10SPRITE GetSpriteHandler() { return this->spriteHandler; }

	// Keyboard related functions 
	void InitKeyboard() {}
	int IsKeyDown(int KeyCode);
	int IsKeyUp(int KeyCode);
	void ProcessKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }

	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void LoadResources();
	ID3D10Device* GetDirect3DDevice() {
		return pD3DDevice;
	}

	ID3D10SamplerState* GetPointSampler() const { return pPointSampler; }

	LPTEXTURE LoadTexture(LPCWSTR texturePath);

	void Draw(float x, float y, int nx, LPTEXTURE tex, int left, int top, int right, int bottom, float width, float height);

	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }


	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }

	CScene* GetCurrentScene()
	{
		return CSceneManager::GetInstance()->GetCurrentScene();
	}
	CPlayScene* GetCurrentPlayScene()
	{
		CScene* playscene = this->GetCurrentScene();
		if (playscene && dynamic_cast<CPlayScene*>(playscene))
			return dynamic_cast<CPlayScene*>(playscene);
		return nullptr;
	}
	static CGame* GetInstance();

	~CGame();
};