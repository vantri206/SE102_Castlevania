#include "BreakableBrick.h"

CBreakableBrick::CBreakableBrick()
{
	LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(BREAKABLEBRICK_ANI_SET_ID);
	this->SetAnimationSet(ani_set);
	this->SetSize(BREAKABLE_BRICK_WIDTH, BREAKABLE_BRICK_HEIGHT);
}

int CBreakableBrick::IsDirectionColliable(int nx, int ny)
{
	if (nx != 0 || ny > 0) return 1;
	return 0;
}

void CBreakableBrick::Render()
{
	if (!this->isInDestroyed())
		animation_set->at(ani_id)->Render(x, y, POSITIVE_DIRECTION, width, height);
}

void CBreakableBrick::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 1)
	{
		this->type = extra_settings[0];
		this->itemdropId = extra_settings[1];
		this->itemDropExtraSettings = vector<int>(extra_settings.begin() + 2, extra_settings.end());
	}
	switch (this->type)
	{
	case 1:
		ani_id = BREAKABLE_BRICK_ANI_BRICK1;
		break;
	case 2:
		ani_id = BREAKABLE_BRICK_ANI_BRICK2;
		break;
	}
}