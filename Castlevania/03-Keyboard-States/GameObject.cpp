#pragma once

#include "GameObject.h"
#include "debug.h"

#define ID_TEX_BBOX 999

CGameObject::CGameObject()
{
	x = y = 0;
	width = height = 0;
	vx = vy = 0;
	nx = ny = 1;
	state = -1;
	isDeleted = false;
}
void CGameObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y + height / 2;
	r = x + width / 2;
	b = y - height / 2;
}
void CGameObject::RenderBoundingBox()
{
	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);
	CGame::GetInstance()->DrawBoundingBox(l, t, r, b);
}
CGameObject::~CGameObject()
{

}