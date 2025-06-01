#pragma once

#include "MorningStar.h"

CMorningStar::CMorningStar()
{
	this->SetSize(MORNINGSTAR_WIDTH, MORNINGSTAR_HEIGHT);
	LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(MORNINGSTAR_ANI_SET_ID);
	this->SetAnimationSet(ani_set);
	this->SetState(MORNINGSTAR_STATE_NORMAL);
}
void CMorningStar::Render()
{
	animation_set->at(MORNINGSTAR_ANI_NORMAL)->Render(x, y, nx, width, height);
}
