#include "MagicCrystal.h"

CMagicCrystal::CMagicCrystal()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(MAGICCRYSTAL_ANI_SET_ID));
	this->ani_id = ID_ANI_MAGICCRYSTAL;
	ay = DEFAULT_GRAVITY;
}