#include <algorithm>
#include "debug.h"
#include "Ghoul.h"
#include <cstdlib>

void CGhoul::Update(DWORD dt)
{

}

void CGhoul::Render()
{
	animation_set->at(ANI_ID_GHOUL_WALK)->Render(x, y);
}

void CGhoul::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->SetDirection(extra_settings[0]);
}
