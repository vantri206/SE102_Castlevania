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

void CCandle::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		object_drop_id = extra_settings[0];
}