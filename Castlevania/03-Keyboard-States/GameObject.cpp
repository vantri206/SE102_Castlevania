#pragma once

#include "GameObject.h"

CGameObject::CGameObject()
{
	x = y = 0;
	width = height = 0;
	vx = vy = 0;
	nx = 1;	
	state = -1;
}
void CGameObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y + height / 2;
	r = x + width/2;
	b = y - height/2;
}
CGameObject::~CGameObject()
{

}