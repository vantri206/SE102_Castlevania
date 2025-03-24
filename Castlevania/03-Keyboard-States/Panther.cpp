#include <algorithm>
#include "debug.h"
#include "PANTHER.h"
#include <cstdlib>

void CPANTHER::Update(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
    int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();

    if (x <= 0 || x >= BackBufferWidth - PANTHER_WIDTH) {
        vx = -vx;
        if (x <= 0)
        {
            x = 0;
        }
        else if (x >= BackBufferWidth - PANTHER_WIDTH)
        {
            x = (float)(BackBufferWidth - PANTHER_WIDTH);
        }
        nx = -nx;
    }

    if (y <= 0 || y >= BackBufferHeight - PANTHER_HEIGHT) {
        vy = -vy;
        if (y <= 0)
        {
            y = 0;
        }
        else if (y >= BackBufferHeight - PANTHER_HEIGHT)
        {
            y = (float)(BackBufferHeight - PANTHER_HEIGHT);
        }
        ny = -ny;
    }
}

void CPANTHER::Render()
{
    int ani_id = -1;
    switch (state)
    {
    case PANTHER_STATE_IDLE:
    {
        ani_id = ANI_ID_PANTHER_IDLE;
        break;
    }
    case PANTHER_STATE_WALK:
    {
        ani_id = ANI_ID_PANTHER_IDLE;
        break;
    }
    }
    animation_set->at(ani_id)->Render(x, y, nx, 0.5f);
}

void CPANTHER::SetState(int state)
{
    switch (state)
    {
    case PANTHER_STATE_IDLE:
    {
        vx = 0;
        vy = 0;
        break;
    }
    case PANTHER_STATE_WALK:
    {
        if (nx > 0) vx = maxVx;
        else vx = -maxVx;
        if (ny > 0) vy = maxVx;
        else vy = -maxVx;
        break;
    }
    }
    CGameObject::SetState(state);
}
