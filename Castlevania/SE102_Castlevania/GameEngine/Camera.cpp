#pragma once
#include "Camera.h"

CCamera* CCamera::__instance = NULL;
CCamera::CCamera(float _x, float _y, float _width, float _height)
    : x(_x), y(_y), width(_width), height(_height) {
}
CCamera* CCamera::GetInstance() {
    if (__instance == NULL) {
        __instance = new CCamera();
    }
    return __instance;
}
void CCamera::SetPosition(float newX, float newY, float mapWidth, float mapHeight) {
    x = max(0.0f, min(newX, mapWidth - width + 16));
    y = max(0.0f, min(newY, mapHeight - height));
}
void CCamera::SetSize(float newWidth, float newHeight) {
    width = newWidth;
    height = newHeight;
}
float CCamera::GetX() {
    return x;
}
float CCamera::GetY() {
    return y;
}
void CCamera::SetX(float _x) {
    x = _x;
}
void CCamera::SetY(float _y) {
    y = _y;
}
float CCamera::GetWidth() {
    return width;
}
float CCamera::GetHeight() {
    return height;
}
bool CCamera::IsInCamera(CGameObject* obj) {
    float objX = obj->GetX();
    float objY = obj->GetY();
    float objWidth = obj->GetWidth();
    float objHeight = obj->GetHeight();

    return (objX + objWidth >= x && objX <= x + width &&
        objY + objHeight >= y && objY <= y + height);
}
void CCamera::Update(DWORD dt, CGameObject* target, float mapWidth, float mapHeight)
{
    CGame* game = CGame::GetInstance();
    float cx = target->GetX() - game->GetBackBufferWidth() / 2;
    float cy = target->GetY() - game->GetBackBufferHeight() / 2;
    SetPosition(cx, 0, mapWidth, mapHeight);
}
RECT CCamera::GetCamRect()
{
	RECT camRect;
	camRect.left = (int)x;
	camRect.bottom = (int)y;
	camRect.right = (int)(x + width);
	camRect.top = (int)(y + height);
	return camRect;
}