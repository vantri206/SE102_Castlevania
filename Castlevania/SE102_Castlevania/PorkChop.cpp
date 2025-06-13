#include "PorkChop.h"

CPorkChop::CPorkChop()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(PORKCHOP_ANI_SET_ID));
	this->SetSize(PORKCHOP_WIDTH, PORKCHOP_HEIGHT);
	this->healValue = PORKCHOP_HEAL_VALUE;
}

int CPorkChop::getHealthValue()
{
	return healValue;
}
