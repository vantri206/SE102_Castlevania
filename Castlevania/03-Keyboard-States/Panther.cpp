#include <algorithm>
#include "debug.h"
#include "Panther.h"
#include <cstdlib>

void CPanther::Update(DWORD dt)
{
   
}

void CPanther::Render()
{
	animation_set->at(ANI_ID_PANTHER_IDLE)->Render(x, y);
}

void CPanther::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->SetDirection(extra_settings[0]);
}
