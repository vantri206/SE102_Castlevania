#pragma once

#include "debug.h"
#include "Game.h"
#include "Sprite.h"
#include "Texture.h"
#include "Textures.h"

#include "Animation.h"
#include "Animations.h"
#include "Sprite.h"
#include "Sprites.h"
#include "PlayScene.h"

#include "Simon.h"
#include "Ghoul.h"
#include "Camera.h"
#include "SampleKeyEventHandler.h"
#include "Utils.h"

#include<fstream>

#include "GameDefine.h"


#define LOAD_RESOURCE_TEXTURES 1
#define LOAD_RESOURCE_SPRITES 2
#define LOAD_RESOURCE_ANIMATIONS 3
#define LOAD_RESOURCE_ANIMATION_SETS 4

CGame* CGame::__instance = NULL;
/*
	Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
	rendering 2D images
	- hWnd: Application window handle
*/
void CGame::Init(HWND hWnd, HINSTANCE hInstance)
{
	for (int i = 0; i < MAX_SCENE; i++)
		scenes[i] = nullptr;

	this->hWnd = hWnd;
	this->hInstance = hInstance;

	// retrieve client area width & height so that we can create backbuffer height & width accordingly 
	RECT r;
	GetClientRect(hWnd, &r);

	backBufferWidth = r.right + 1;
	backBufferHeight = r.bottom + 1;

	// Create & clear the DXGI_SWAP_CHAIN_DESC structure
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Fill in the needed values
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = backBufferWidth;
	swapChainDesc.BufferDesc.Height = backBufferHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	// Create the D3D device and the swap chain
	HRESULT hr = D3D10CreateDeviceAndSwapChain(NULL,
		D3D10_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		D3D10_SDK_VERSION,
		&swapChainDesc,
		&pSwapChain,
		&pD3DDevice);

	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] D3D10CreateDeviceAndSwapChain has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	// Get the back buffer from the swapchain
	ID3D10Texture2D* pBackBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);
	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] pSwapChain->GetBuffer has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	// create the render target view
	hr = pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

	pBackBuffer->Release();
	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] CreateRenderTargetView has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	// set the render target
	pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	// create and set the viewport
	D3D10_VIEWPORT viewPort;
	viewPort.Width = backBufferWidth;
	viewPort.Height = backBufferHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	pD3DDevice->RSSetViewports(1, &viewPort);


	// create the sprite object to handle sprite drawing 
	hr = D3DX10CreateSprite(pD3DDevice, 0, &spriteHandler);

	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] D3DX10CreateSprite has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	D3DXMATRIX matProjection;

	// Create the projection matrix using the values in the viewport
	D3DXMatrixOrthoOffCenterLH(&matProjection,
		(float)viewPort.TopLeftX,
		(float)viewPort.Width,
		(float)viewPort.TopLeftY,
		(float)viewPort.Height,
		0.1f,
		10);
	hr = spriteHandler->SetProjectionTransform(&matProjection);

	// Initialize the blend state for alpha drawing
	D3D10_BLEND_DESC StateDesc;
	ZeroMemory(&StateDesc, sizeof(D3D10_BLEND_DESC));
	StateDesc.AlphaToCoverageEnable = FALSE;
	StateDesc.BlendEnable[0] = TRUE;
	StateDesc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	StateDesc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	StateDesc.BlendOp = D3D10_BLEND_OP_ADD;
	StateDesc.SrcBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	StateDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
	pD3DDevice->CreateBlendState(&StateDesc, &this->pBlendStateAlpha);

	CTextures::GetInstance()->SetDevice(pD3DDevice);
	DebugOut((wchar_t*)L"[INFO] InitDirectX has been successful\n");

	D3D10_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D10_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D10_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D10_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D10_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D10_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D10_FLOAT32_MAX;

	hr = pD3DDevice->CreateSamplerState(&sampDesc, &pPointSampler);
	
	return;
}
/*
	Draw the whole texture or part of texture onto screen
	NOTE: This function is very inefficient because it has to convert
	from texture to sprite every time we need to draw it
*/	
LPTEXTURE CGame::LoadTexture(LPCWSTR texturePath)
{
	ID3D10Resource* pD3D10Resource = NULL;
	ID3D10Texture2D* tex = NULL;

	// Loads the texture into a temporary ID3D10Resource object
	D3DX10_IMAGE_LOAD_INFO loadInfo = {};
	loadInfo.MipLevels = 1; // chỉ level 0
	HRESULT hr = D3DX10CreateTextureFromFile(pD3DDevice,
		texturePath,
		&loadInfo,
		NULL,
		&pD3D10Resource,
		NULL);

	// Make sure the texture was loaded successfully
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] Failed to load texture file: %s with error: %d\n", texturePath, hr);
		return NULL;
	}

	// Translates the ID3D10Resource object into a ID3D10Texture2D object
	pD3D10Resource->QueryInterface(__uuidof(ID3D10Texture2D), (LPVOID*)&tex);
	pD3D10Resource->Release();

	if (!tex) {
		DebugOut((wchar_t*)L"[ERROR] Failed to convert from ID3D10Resource to ID3D10Texture2D \n");
		return NULL;
	}

	//
	// Create the Share Resource View for this texture 
	// 	   
	// Get the texture details
	D3D10_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	// Create a shader resource view of the texture
	D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;

	// Clear out the shader resource view description structure
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));

	// Set the texture format
	SRVDesc.Format = desc.Format;

	// Set the type of resource
	SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = desc.MipLevels;

	ID3D10ShaderResourceView* gSpriteTextureRV = NULL;

	pD3DDevice->CreateShaderResourceView(tex, &SRVDesc, &gSpriteTextureRV);

	DebugOut(L"[INFO] Texture loaded Ok from file: %s \n", texturePath);

	return new CTexture(tex, gSpriteTextureRV);
}

void CGame::Draw(float x, float y, int nx, LPTEXTURE tex, int left, int top, int right, int bottom, float width, float height)
{
	if (tex == NULL) return;

	int spriteWidth = right - left + 1;
	int spriteHeight = bottom - top + 1;

	D3DX10_SPRITE sprite;

	sprite.pTexture = tex->getShaderResourceView();


	sprite.TexCoord.x = (float)left / tex->getWidth();
	sprite.TexCoord.y = (float)top / tex->getHeight();

	sprite.TexSize.x = (float)spriteWidth / tex->getWidth();
	sprite.TexSize.y = (float)spriteHeight / tex->getHeight();

	sprite.TextureIndex = 0;
	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	if (nx > 0)
	{
		sprite.TexCoord.x = ((float)left + spriteWidth) / tex->getWidth();
		sprite.TexSize.x = -sprite.TexSize.x;
	}


	float cx = (FLOAT)floor(CCamera::GetInstance()->GetX());
	float cy = (FLOAT)floor(CCamera::GetInstance()->GetY());

	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, round(x - cx), round(y - cy), 0.1f);



	D3DXMATRIX matScaling;
	D3DXMatrixScaling(&matScaling, width, height, 1.0f);

	sprite.matWorld = matScaling * matTranslation;
	// 6) Gán point-filtering ngay trước draw
	ID3D10SamplerState* pt = pPointSampler; // hoặc g->GetPointSampler()
	pD3DDevice->PSSetSamplers(0, 1, &pt);
	spriteHandler->DrawSpritesImmediate(&sprite, 1, 0, 0);
}


void CGame::DrawBoundingBox(float left, float top, float right, float bottom)
{
	LPTEXTURE bbox = CTextures::GetInstance()->Get(999); 
	if (!bbox) return;

	float width = right - left + 1;
	float height = top - bottom + 1;

	float x = (left + right) / 2;
	float y = (bottom + top) / 2;

	Draw(x, top, 1, bbox, 0, 0, 1, 1, width - 2, 1.0f);

	Draw(x, bottom, 1, bbox, 0, 0, 1, 1, width - 2, 1.0f);

	Draw(left, y, 1, bbox, 0, 0, 1, 1, 1.0f, height);

	Draw(right, y, 1, bbox, 0, 0, 1, 1, 1.0f, height);
}

void CGame::LoadScene(int id, int mapId, LPCWSTR mapFile, LPCWSTR objFile)
{
	if (id < 0 || id >= MAX_SCENE) return;

	if (scenes[id])		//delete old scene
	{
		scenes[id]->~CScene();
		delete scenes[id];
		scenes[id] = nullptr;
	}

	scenes[id] = new CScene(id, mapId, mapFile, objFile);
}

void CGame::ChangeScene(int id)
{
	if (id < 0 || id >= MAX_SCENE) return;
	currentSceneId = id;
}


int CGame::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

int CGame::IsKeyUp(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) == 0;
}

void CGame::InitKeyboard(LPKEYEVENTHANDLER handler)
{
	HRESULT hr = DirectInput8Create(this->hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&di, NULL);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	this->keyHandler = handler;

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void CGame::ProcessKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	keyHandler->KeyState((BYTE*)&keyStates);

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}

void _ParseSection_TEXTURES(LPCWSTR filepath)
{
	//DebugOut(L"[INFO] Load texture %d from file %s\n", 123, filepath);
	ifstream f;
	f.open(filepath);
	char str[MAX_TXT_LINE];
	while (f.getline(str, MAX_TXT_LINE))
	{
		string line(str);
		//DebugOut(L"[INFO] Load texture %d from file %s\n", 123, line);
		if (line[0] == '#') continue;
		if (line.empty()) continue;

		vector<string> tokens = split(line);

		if (tokens.size() < 2) return;

		int texID = atoi(tokens[0].c_str());
		wstring path = ToWSTR(tokens[1]);

		CTextures::GetInstance()->Add(texID, path.c_str());

	}
	f.close();
}

void _ParseSection_SPRITES(LPCWSTR filepath)
{
	ifstream f;
	f.open(filepath);
	char str[MAX_TXT_LINE];
	while (f.getline(str, MAX_TXT_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;
		if (line.empty()) continue;
		vector<string> tokens = split(line);

		if (tokens.size() < 6) return;

		int ID = atoi(tokens[0].c_str());
		int l = atoi(tokens[1].c_str());
		int t = atoi(tokens[2].c_str());
		int r = atoi(tokens[3].c_str());
		int b = atoi(tokens[4].c_str());
		int texID = atoi(tokens[5].c_str());


		LPTEXTURE tex = CTextures::GetInstance()->Get(texID);

		if (tex == NULL)
		{
			//DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
			return;
		}

		//DebugOut(L"[ERROR] Texture ID: 123 + %d!\n", texID);
		CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
	}
	f.close();
}


void _ParseSection_ANIMATIONS(LPCWSTR filepath)
{
	ifstream f;
	f.open(filepath);
	char str[MAX_TXT_LINE];
	while (f.getline(str, MAX_TXT_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;
		if (line.empty()) continue;
		vector<string> tokens = split(line);

		if (tokens.size() < 3) return;

		LPANIMATION ani = new CAnimation(0);

		int ani_id = atoi(tokens[0].c_str());
		for (int i = 1; i < tokens.size(); i += 2)
		{
			int sprite_id = atoi(tokens[i].c_str());
			int frame_time = atoi(tokens[i + 1].c_str());
			ani->Add(sprite_id, frame_time);
			//DebugOut(L"[ERROR] Texture ID %d found!\n", sprite_id);
		}
		CAnimations::GetInstance()->Add(ani_id, ani);
	}
	f.close();
}

void _ParseSection_ANIMATION_SETS(LPCWSTR filepath)
{
	ifstream f;
	f.open(filepath);
	char str[MAX_TXT_LINE];
	while (f.getline(str, MAX_TXT_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;
		if (line.empty()) continue;
		vector<string> tokens = split(line);

		if (tokens.size() < 2) return;


		int ani_set_id = atoi(tokens[0].c_str());

		LPANIMATION_SET s = new CAnimationSet();

		CAnimations* animations = CAnimations::GetInstance();

		for (int i = 1; i < tokens.size(); i++)
		{
			int ani_id = atoi(tokens[i].c_str());

			LPANIMATION ani = animations->Get(ani_id);
			s->push_back(ani);
		}

		CAnimationSets::GetInstance()->Add(ani_set_id, s);
	}
	f.close();
}

void CGame::LoadResources()
{

	for(int i = 1; i <= 4; i++)
	{
		switch(i)
		{
		case LOAD_RESOURCE_TEXTURES: _ParseSection_TEXTURES(TEXTURES_PATH); break;
		case LOAD_RESOURCE_SPRITES: _ParseSection_SPRITES(SPRITES_PATH); break;
		case LOAD_RESOURCE_ANIMATIONS: _ParseSection_ANIMATIONS(ANIMATIONS_PATH); break;
		case LOAD_RESOURCE_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(ANIMATIONS_SET_PATH); break;
		}
	}

	//DebugOut(L"[INFO] Done loading game resources");

}


CGame::~CGame()
{
	pBlendStateAlpha->Release();
	spriteHandler->Release();
	pRenderTargetView->Release();
	pSwapChain->Release();
	pD3DDevice->Release();
}

CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

void CGame::DrawFillRect(RECT rect, D3DXCOLOR color)
{
    // Create a 1x1 white texture if not exists
    static ID3D10Texture2D* whiteTex = nullptr;
    static ID3D10ShaderResourceView* whiteTexView = nullptr;
    
    if (whiteTex == nullptr)
    {
        D3D10_TEXTURE2D_DESC texDesc;
        ZeroMemory(&texDesc, sizeof(texDesc));
        texDesc.Width = 1;
        texDesc.Height = 1;
        texDesc.MipLevels = 1;
        texDesc.ArraySize = 1;
        texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        texDesc.SampleDesc.Count = 1;
        texDesc.Usage = D3D10_USAGE_DEFAULT;
        texDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;

        UINT white = 0xFFFFFFFF;
        D3D10_SUBRESOURCE_DATA initData;
        initData.pSysMem = &white;
        initData.SysMemPitch = sizeof(UINT);
        initData.SysMemSlicePitch = 0;

        HRESULT hr = pD3DDevice->CreateTexture2D(&texDesc, &initData, &whiteTex);
        if (FAILED(hr))
            return;

        D3D10_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;

        hr = pD3DDevice->CreateShaderResourceView(whiteTex, &srvDesc, &whiteTexView);
        if (FAILED(hr))
            return;
    }

    D3DX10_SPRITE sprite;
    sprite.pTexture = whiteTexView;
    sprite.TexCoord.x = 0.0f;
    sprite.TexCoord.y = 0.0f;
    sprite.TexSize.x = 1.0f;
    sprite.TexSize.y = 1.0f;
    sprite.ColorModulate = color;
    sprite.TextureIndex = 0;

    D3DXMATRIX matWorld;
    D3DXMatrixIdentity(&matWorld);

    D3DXMATRIX matTranslation;
    D3DXMatrixTranslation(&matTranslation, (float)rect.left, (float)rect.top, 0.0f);

    D3DXMATRIX matScaling;
    D3DXMatrixScaling(&matScaling, (float)(rect.right - rect.left), (float)(rect.bottom - rect.top), 1.0f);

    matWorld = matScaling * matTranslation;
    sprite.matWorld = matWorld;

    this->spriteHandler->DrawSpritesImmediate(&sprite, 1, 0, 0);
}
