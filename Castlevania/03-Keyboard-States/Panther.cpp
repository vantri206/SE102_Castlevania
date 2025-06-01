#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Panther.h"
#include "Whip.h"
#include "Enemy.h"
#include <cstdlib>

CPanther::CPanther()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(PANTHER_ANI_SET_ID));
	this->SetState(PANTHER_STATE_IDLE);
	this->SetAniId(ANI_ID_PANTHER_IDLE);
	this->ay = GRAVITY;
	health = 1;
}
void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isActived())
	{
		CSimon* player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
		if (this->CheckEnemyCanActive(player)) ActiveEnemy();
	}

	if (!isActived()) return;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (this->isDead())
	{
		if (GetTickCount64() - startDeathTime >= ENEMY_DEAD_TIME)
			isDeleted = true;
	}
	else if (this->health <= 0)
	{
		this->SetState(PANTHER_STATE_DEAD);
		this->NormalEnemyDead(ENEMY_DEAD_TIME);
	}
	else if (vy < 0 && !isHovering())
	{
		this->SetState(PANTHER_STATE_HOVERING);
		this->vy = PANTHER_JUMP_VY;
	}
	vx += ax * dt;
	vy += ay * dt;
}

void CPanther::Render()
{
	if (!this->isDead())
		animation_set->at(ani_id)->Render(x, y, nx, width, height);
}

void CPanther::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CPanther::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj)) return;
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0.0f;
		if (isHovering())
		{
			this->nx = (-1) * this->nx;
			this->vx = (-1) * this->vx;
			this->SetState(PANTHER_STATE_RUN);
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0.0f;
	}
}

void CPanther::SetState(int state)
{
	switch (state)
	{
	case PANTHER_STATE_IDLE:
		this->SetAniId(ANI_ID_PANTHER_IDLE);
		break;
	case PANTHER_STATE_RUN:
		this->SetAniId(ANI_ID_PANTHER_WALK);
		break;
	case PANTHER_STATE_HOVERING:
		this->SetAniId(ANI_ID_PANTHER_HOVERING);
	case PANTHER_STATE_DEAD:
		break;
	}
	this->state = state;
}

int CPanther::IsCollidable()
{
	return !(this->isDead());
}
void CPanther::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->SetDirectionX(extra_settings[0]);
}
int CPanther::CheckEnemyCanActive(CSimon* simon)
{
	float x = simon->GetX();
	if (abs(x - this->x) <= PANTHER_RANGE_ACTIVE) return 1;
	return 0;
}
void CPanther::ActiveEnemy()
{
	CEnemy::ActiveEnemy();
	CSimon* player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	if (player->GetX() < this->x) this->nx = -1;
	else this->nx = 1;
	this->SetState(PANTHER_STATE_RUN);
	this->SetSpeed(PANTHER_RUN_SPEED * nx, 0.0f);
}
int CPanther::isHovering()
{
	return (this->state == PANTHER_STATE_HOVERING);
}
bool CPanther::isDead()
{
	return (this->state == PANTHER_STATE_DEAD);
}