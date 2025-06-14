#include "MagicCrystal.h"

CMagicCrystal::CMagicCrystal()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(MAGICCRYSTAL_ANI_SET_ID));
	this->ani_id = ID_ANI_MAGICCRYSTAL;
	ay = DEFAULT_GRAVITY;
	startAppearing = GetTickCount64();
	this->SetSize(MAGICCRYSTAL_WIDTH, MAGICCRYSTAL_HEIGHT);
	this->SetType(MAGICCRYSTAL);
}

void CMagicCrystal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (IsDeleted()) return;
	if (startAppearing && GetTickCount64() - startAppearing >= CRYSTAL_HEART_FALLING_TIME)
		vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}