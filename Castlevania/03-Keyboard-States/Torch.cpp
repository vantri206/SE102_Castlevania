#pragma once

#include "Torch.h"

CTorch::CTorch()
{
	LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(TORCH_ANI_SET_ID);
	this->SetAnimationSet(ani_set);
}
void CTorch::Render()
{
	animation_set->at(TORCH_STATE_BURN)->Render(x, y);
}

void CTorch::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		object_drop_id = extra_settings[0];
}