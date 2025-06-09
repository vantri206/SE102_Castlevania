#pragma once

#include "MorningStar.h"

CMorningStar::CMorningStar()
{
	this->SetSize(MORNINGSTAR_WIDTH, MORNINGSTAR_HEIGHT);
	ay = DEFAULT_GRAVITY;

	LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(MORNINGSTAR_ANI_SET_ID);
	this->SetAnimationSet(ani_set);
	this->SetState(MORNINGSTAR_STATE_NORMAL);
}
