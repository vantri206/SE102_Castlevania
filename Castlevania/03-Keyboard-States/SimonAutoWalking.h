#pragma once
#include "SimonState.h"
#include "Stair.h"
class CSimonAutoWalking : public CSimonState
{
	float targetX;
	int stairDirection;
	bool goingUp; 

public:
	CSimonAutoWalking(CSimon* simon, float x, int direction, bool isGoingUp);
	void KeyDownHandle(CSimon* simon, int keyCode) ;
	void KeyUpHandle(CSimon* simon, int keyCode) ;
	void Update(CSimon* simon, DWORD dt) ;
	void OnNoCollision(CSimon* simon, DWORD dt) ;
	void OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e) ;
};
