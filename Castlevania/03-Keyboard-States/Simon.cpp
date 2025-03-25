#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Game.h"

void CSimon::Update(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;

    // Cập nhật cây roi
    whip->Update(dt);

    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
    int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();

    if (y <= 0 || y >= BackBufferHeight - SIMON_HEIGHT) {
        if (y <= 0)
            y = 0;
        else if (y >= BackBufferHeight - SIMON_HEIGHT)
            y = (float)(BackBufferHeight - SIMON_HEIGHT);
    }
}

void CSimon::Render()
{
    if (animation_set == nullptr) {
        DebugOut(L"[ERROR] Simon animation set is null!\n");
        return;
    }
    animation_set->at(ani_id)->Render(x, y, nx, 0.5f);

    // Chỉ render cây roi khi ở trạng thái tấn công
    if (state == SIMON_STATE_ATTACK) {
        whip->Render();
    }
}

void CSimon::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case SIMON_STATE_IDLE:
    {
        this->SimonIdle();
        ani_id = ID_ANI_SIMON_IDLE;
        break;
    }
    case SIMON_STATE_WALK:
    {
        this->SimonWalk();
        ani_id = ID_ANI_SIMON_WALK;
        break;
    }
    case SIMON_STATE_ATTACK:
    {
        this->SimonAttack();
        ani_id = ID_ANI_SIMON_ATTACK;
        break;
    }
    case SIMON_STATE_GO_UP:
    {
        this->SimonWalkUp();
        ani_id = ID_ANI_SIMON_GO_UP;
        break;
    }
    }
}

void CSimon::SimonWalkUp()
{
    vx = 0;
    if (ny > 0) vy = -SIMON_WALKING_SPEED;
    else vy = SIMON_WALKING_SPEED;
}

void CSimon::SimonWalk()
{
    vy = 0;
    if (nx > 0) vx = SIMON_WALKING_SPEED;
    else vx = -SIMON_WALKING_SPEED;
}

void CSimon::SimonAttack()
{
    vx = 0;
    vy = 0;
}

void CSimon::SimonIdle()
{
    vx = 0;
    vy = 0;
}

void CSimon::SimonSit()
{
    vx = 0;
    vy = 0;
}void GetBoundingBox()
{

}