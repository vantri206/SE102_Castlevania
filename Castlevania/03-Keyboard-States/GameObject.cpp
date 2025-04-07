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
CGameObject::~CGameObject()
{

}