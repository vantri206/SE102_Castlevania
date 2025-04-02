#include <algorithm>
#include "debug.h"
#include "Ghoul.h"
#include <cstdlib>

void CGhoul::Update(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
    int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();

    if (x <= 0 || x >= BackBufferWidth - GHOUL_WIDTH) {
        vx = -vx;
        if (x <= 0)
        {
            x = 0;
        }
        else if (x >= BackBufferWidth - GHOUL_WIDTH)
        {
            x = (float)(BackBufferWidth - GHOUL_WIDTH);
        }
        nx = -nx;
    }

    if (y <= 0 || y >= BackBufferHeight - GHOUL_HEIGHT) {
        vy = -vy;
        if (y <= 0)
        {
            y = 0;
        }
        else if (y >= BackBufferHeight - GHOUL_HEIGHT)
        {
            y = (float)(BackBufferHeight - GHOUL_HEIGHT);
        }
        ny = -ny;
    }
}

void CGhoul::Render()
{
    int ani_id = -1;
    switch (state)
    {
    case GHOUL_STATE_IDLE:
    {
        ani_id = ANI_ID_GHOUL_IDLE;
        break;
    }
    case GHOUL_STATE_WALK:
    {
        ani_id = ANI_ID_GHOUL_WALK;
        break;
    }
    }
    animation_set->at(ani_id)->Render(x, y, nx, 0.5f);
}

void CGhoul::SetState(int state)
{
    switch (state)
    {
        case GHOUL_STATE_IDLE:
        {
            vx = 0;
            vy = 0;
            break;
        }
        case GHOUL_STATE_WALK:
        {
            if (nx > 0) vx = maxVx;
            else vx = -maxVx;
            if (ny > 0) vy = maxVy;
            else vy = -maxVy;
            break;
        }
    }
   // CGameObject::SetState(state);
}
