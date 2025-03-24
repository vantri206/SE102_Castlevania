#include <algorithm>
#include "debug.h"

#include "PlayScene.h"


#include "Simon.h"
#include "Game.h"

void CSimon::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	int mapwidth = (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetWidth());

	if (x <= 0 || x >= mapwidth - SIMON_WIDTH) 
  {
		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= mapwidth - SIMON_WIDTH)
		{
			x = (float)(mapwidth - SIMON_WIDTH);
		}
	}
    // Cập nhật cây roi
    whip->Update(dt);
}

void CSimon::Render()
{
    if (animation_set == nullptr) {
        DebugOut(L"[ERROR] Simon animation set is null!\n");
        return;
    }
  	animation_set->at(ani_id)->Render(x, y, nx, SIMON_SIZE);
    whip->Render();  // Render cây roi
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
            whip->Deactivate();
            break;
        }
        case SIMON_STATE_WALK:
        {
            this->SimonWalk();
            ani_id = ID_ANI_SIMON_WALK;
            whip->Deactivate();
            break;
        }
        case SIMON_STATE_ATTACK:
        {
            this->SimonAttack();
            ani_id = ID_ANI_SIMON_ATTACK;
            whip->Activate();  // Kích hoạt cây roi khi tấn công
            break;
        }
        case SIMON_STATE_GO_UP:
        {
            this->SimonWalkUp();
            ani_id = ID_ANI_SIMON_GO_UP;
            whip->Deactivate();
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
