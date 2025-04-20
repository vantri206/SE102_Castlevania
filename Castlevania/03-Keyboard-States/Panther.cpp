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

void CPanther::SetState(int state)
{
    
}
