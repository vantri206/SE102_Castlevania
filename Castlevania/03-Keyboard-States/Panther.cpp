#include <algorithm>
#include "debug.h"
#include "Panther.h"
#include <cstdlib>

CPanther::CPanther()
{
	vx = vy = 0.0f;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(PANTHER_ANI_SET_ID));
	this->SetState(PANTHER_STATE_IDLE);
	this->SetAniId(ANI_ID_PANTHER_IDLE);

	health = 1;
}
void CPanther::Update(DWORD dt)
{
   
}

void CPanther::Render()
{
	animation_set->at(ANI_ID_PANTHER_IDLE)->Render(x, y, nx, width, height);
}

void CPanther::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->SetDirection(extra_settings[0]);
}
