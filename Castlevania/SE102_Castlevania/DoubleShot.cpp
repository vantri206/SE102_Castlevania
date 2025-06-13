#include "DoubleShot.h"

CDoubleShot::CDoubleShot()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(DOUBLESHOT_ANI_SET_ID));
	this->SetAniId(ID_ANI_DOUBLESHOT);
	this->SetSize(DOUBLESHOT_WIDTH, DOUBLESHOT_HEIGHT);
	ay = DEFAULT_GRAVITY;
}
