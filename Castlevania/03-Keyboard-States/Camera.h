#pragma once
#include "GameObject.h"
#include <algorithm>

class CCamera {
	static CCamera* __instance;
private: 
	float x, y;
	float width, height;
public:
	CCamera(float _x = 0, float _y = 0, float _width = 360, float _height = 192)
		: x(_x), y(_y), width(_width), height(_height) {
	}
	static CCamera* GetInstance();
	void SetPosition(float newX, float newY,float mapWidth, float mapHeight) { 
		x =  max(0.0f,  min(newX, mapWidth - width));
		y =  max(0.0f,  min(newY, mapHeight - height));
	}
	void SetSize(float width, float height) { this->width = width; this->height = height; }
	float GetX() { return x; }
	float GetY() { return y; }
	void SetX(float _x) { x = _x; }
	void SetY(float _y) { y = _y; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }
	void Move(float dx, float dy) {
		x += dx;
		y += dy;
	}
	bool IsInCamera(CGameObject* obj) {
		float objX = obj->GetX();
		float objY = obj->GetY();
		float objWidth = obj->GetWidth();
		float objHeight = obj->GetHeight();

		return (objX + objWidth >= x && objX <= x + width &&
			objY + objHeight >= y && objY <= y + height);
	}
	void Update(DWORD dt, CGameObject* target, float mapWidth, float mapHeight) {
		SetPosition(target->GetX() - width / 2, target->GetY() - height / 2,mapWidth,mapHeight);

	}
};
