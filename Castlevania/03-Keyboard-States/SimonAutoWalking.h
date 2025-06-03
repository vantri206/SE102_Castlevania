#pragma onc
#include "SimonState.h"
#include "Stair.h"
enum AutoWalkPurpose
{
	WALK_TO_STAIR_UP,
	WALK_TO_STAIR_DOWN,
	WALK_TO_GATE,
	WALK_TO_POSITION,
	// Thêm các mục đích khác nếu cần
};

class CSimonAutoWalking : public CSimonState
{
	float targetX;
	int stairDirection;
	AutoWalkPurpose purpose;

public:
	CSimonAutoWalking(CSimon* simon, float x, int direction, AutoWalkPurpose purpose);
	void KeyDownHandle(CSimon* simon, int keyCode);
	void KeyUpHandle(CSimon* simon, int keyCode);
	void Update(CSimon* simon, DWORD dt);
	void OnNoCollision(CSimon* simon, DWORD dt);
	void OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e);
};
