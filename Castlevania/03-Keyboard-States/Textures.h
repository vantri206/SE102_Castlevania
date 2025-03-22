#pragma once
#include <unordered_map>
#include <d3d10.h>
#include <d3dx10.h>

class CTextures
{
    static CTextures* __instance;
    static ID3D10Device* pD3DDevice; 

    std::unordered_map<int, LPTEXTURE> textures;

    int tilesetId = 1000;

public:
    CTextures() {}
    static void SetDevice(ID3D10Device* device) { pD3DDevice = device; }
    void Add(int id, LPCWSTR filePath);
    int AddTileset(LPCWSTR filePath);
    LPTEXTURE Get(unsigned int id);
    static CTextures* GetInstance();
};
