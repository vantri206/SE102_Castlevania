#include "ButtonStart.h"

CButtonStart::CButtonStart(float x, float y)
{
	nx = POSITIVE_DIRECTION;
	this->SetPosition(x, y);
	this->SetSize(BUTTON_START_WIDTH, BUTTON_START_HEIGHT);
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(BUTTONSTART_ANI_SET_ID));
	this->ani_id = ANI_ID_BUTTONSTART_NOTPRESSED;
}

void CButtonStart::Render()
{
	animation_set->at(ani_id)->Render(x, y, nx, width, height);
}

void CButtonStart::ButtonPressed()
{
	this->ani_id = ANI_ID_BUTTONSTART_PRESSED;
}
