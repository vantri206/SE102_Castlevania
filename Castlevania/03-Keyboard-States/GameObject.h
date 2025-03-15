#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include "Animation.h"
#include "Animations.h"

using namespace std;

class CGameObject
{
protected:
	float x; 
	float y;

	float vx;
	float vy;

	int nx;	 

	int state;

	CAnimationSet animations;
	LPANIMATION_SET animation_set;
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }

	CGameObject();
	CGameObject(float x, float y):CGameObject() { this->x = x; this->y = y; }

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	~CGameObject();
};

typedef CGameObject* LPGAMEOBJECT;