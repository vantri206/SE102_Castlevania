#pragma once
#include <Windows.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

CTextures* CTextures::__instance = nullptr;

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


LPTEXTURE CTextures::Get(unsigned int id)
{
    if (textures.find(id) != textures.end())
        return textures[id];
    return nullptr;
}

int CTextures::AddTileset(LPCWSTR filePath)
{
    int id = ++tilesetId;
    Add(id, filePath);  
    return id;
}


