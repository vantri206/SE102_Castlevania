#pragma once
#include <Windows.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

CTextures* CTextures::__instance = nullptr;
ID3D10Device* CTextures::pD3DDevice = nullptr;

CTextures* CTextures::GetInstance()
{
    if (__instance == nullptr)
        __instance = new CTextures();
    return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath)
{
	DebugOut(L"\n[INFO] Loading texture from file: %s \n", filePath);
    textures[id] = CGame::GetInstance()->LoadTexture(filePath);
}

void CTextures::AddTilesMap(int mapId, int tileWidth, int tileHeight, int tilesetColumns, int tileCount)
{
	DebugOut(L"\n[INFO] Loading tileset map %d with tile size %d x %d and %d tiles and %d\n", mapId, tileWidth, tileHeight, tileCount, tilesetColumns);
    CTexture* mapTexture = Get(mapId);
    for (int i = 0; i < tileCount; i++)
    {
        int left = (i % tilesetColumns) * tileWidth;
        int top = (i / tilesetColumns) * tileHeight;
        int right = left + tileWidth - 1;
		int bottom = top + tileHeight - 1;

        CTexture* tileTexture = mapTexture->Cut(left, top, right, bottom, pD3DDevice);

        int tileId = mapId * 1000 + i;
        textures[tileId] = tileTexture;
    }
}

LPTEXTURE CTextures::Get(unsigned int id)
{
    if (textures.find(id) != textures.end())
        return textures[id];
    return nullptr;
}