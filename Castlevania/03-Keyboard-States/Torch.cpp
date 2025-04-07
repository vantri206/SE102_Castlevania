#pragma once

#include "Torch.h"

void CTorch::Render()
{
	animation_set->at(TORCH_STATE_BURN)->Render(x, y, 1);
}