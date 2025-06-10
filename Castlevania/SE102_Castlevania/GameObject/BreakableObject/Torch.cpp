#include "Torch.h"
#include "GameSetting.h"

CTorch::CTorch()
{
	LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(TORCH_ANI_SET_ID);
	this->SetAnimationSet(ani_set);
	this->SetSize(TORCH_WIDTH, TORCH_HEIGHT);
}
void CTorch::Render()
{
	if (!this->isInDestroyed())
		animation_set->at(TORCH_STATE_BURN)->Render(x, y, nx, width, height);
}