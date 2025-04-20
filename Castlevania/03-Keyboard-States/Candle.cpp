#pragma once

#include "Candle.h"

CCandle::CCandle()
{
	LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(CANDLE_ANI_SET_ID);
	this->SetAnimationSet(ani_set);
}
void CCandle::Render()
{
	animation_set->at(CANDLE_STATE_BURN)->Render(x, y);
}