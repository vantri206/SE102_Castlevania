#pragma once

#include "Game.h"

class CSprite
{
    int id;                             
    int left;
    int top;
    int right;
    int bottom;

    D3DXMATRIX matWorld;
    LPTEXTURE texture;
    D3DX10_SPRITE sprite;              
    D3DXMATRIX matScaling;             
public:
    CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex);

    void Draw(float x, float y, int nx)
    { 
        this->Draw(x, y, nx, (right - left + 1) / 2, (bottom - top + 1) / 2);
    }
    void Draw(float x, float y, int nx, float width, float height);
};

typedef CSprite* LPSPRITE;
