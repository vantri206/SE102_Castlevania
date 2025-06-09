#include "BigHeart.h"

CBigHeart::CBigHeart()
{
    SetSize(BIG_HEART_WIDTH, BIG_HEART_HEIGHT);
    ay = HEART_GRAVITY;
    heartValue = BIGHEART_HEART_VALUE;

    animation_set = CAnimationSets::GetInstance()->Get(BIGHEART_ANI_SET_ID);
    ani_id = ID_ANI_BIGHEART;
}

int CBigHeart::getHeartValue()
{
    return heartValue;
}
