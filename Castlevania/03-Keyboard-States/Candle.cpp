#pragma once

#include "Candle.h"

CCandle::CCandle()
{
	this->SetSize(CANDLE_WIDTH, CANDLE_HEIGHT);
	LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(CANDLE_ANI_SET_ID);
	this->SetAnimationSet(ani_set);
	this->SetState(CANDLE_STATE_BURN);
}
void CCandle::Render()
{
	animation_set->at(CANDLE_STATE_BURN)->Render(x, y, nx, width, height);
}

void CCandle::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		object_drop_id = extra_settings[0];
}