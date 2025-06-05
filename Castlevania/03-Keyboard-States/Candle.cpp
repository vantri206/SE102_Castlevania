#pragma once
#include "Candle.h"
CCandle::CCandle()
{
    this->SetSize(CANDLE_WIDTH, CANDLE_HEIGHT);
    LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(CANDLE_ANI_SET_ID);
    this->SetAnimationSet(ani_set);
    this->SetState(CANDLE_STATE_BURN);
}
CCandle::CCandle(float x, float y)
{
    this->x = x;
    this->y = y - 16; // bắt đầu thấp hơn một chút
    this->targetY = y;
    this->appearStartY = this->y;
}
void CCandle::StartAppearing()
{
    appearing = true;
}
void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (appearing)
    {
        if (y < targetY)
        {
            y += appearSpeed * dt;
            if (y >= targetY)
            {
                y = targetY;
                appearing = false;
            }
        }
    }
}
void CCandle::Render()
{
    animation_set->at(CANDLE_STATE_BURN)->Render(x, y, nx, width, height);
}
void CCandle::LoadExtraSetting(vector<int> extra_settings)
{
    if (extra_settings.size() > 0)
        object_drop_id = extra_settings[0];
}