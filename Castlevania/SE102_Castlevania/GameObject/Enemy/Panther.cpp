#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Panther.h"
#include "Whip.h"
#include "Enemy.h"
#include <cstdlib>
#include <BreakableBrick.h>

CPanther::CPanther()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(PANTHER_ANI_SET_ID));
	this->SetState(PANTHER_STATE_IDLE);
	this->SetAniId(ANI_ID_PANTHER_IDLE);
	this->SetSize(PANTHER_WIDTH, PANTHER_HEIGHT);
	this->ay = DEFAULT_GRAVITY;

	health = PANTHER_HP;
}
void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!(isDead() || isActived()))
	{
		CSimon* player = CSceneManager::GetInstance()->GetPlayer();
		if (this->CheckEnemyCanActive(player)) ActiveEnemy();
	}

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
	else
	{
		if (this->isActived())
			vx = PANTHER_RUN_SPEED * nx;
		if (vy < 0 && !isHovering())
		{
			this->SetState(PANTHER_STATE_HOVERING);
			this->vy = PANTHER_JUMP_VY;
		}
		else vy += ay * dt;
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
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
	if (e->ny > 0 && e->obj->IsBlocking())
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

int CPanther::CanCollisionWithObj(CGameObject* objDest)
{
	if (isHovering() && vy > 0 && (dynamic_cast<CBrick*>(objDest) || dynamic_cast<CBreakableBrick*>(objDest)))
		return 0;
	return 1;
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
	CSimon* player = CSceneManager::GetInstance()->GetPlayer();
	if (player->GetX() < this->x) this->nx = -1;
	else this->nx = 1;
	this->SetState(PANTHER_STATE_RUN);
	this->SetSpeed(PANTHER_RUN_SPEED * nx, 0.0f);
}
int CPanther::isHovering()
{
	return (this->state == PANTHER_STATE_HOVERING);
}
int CPanther::isDead()
{
	return (this->state == PANTHER_STATE_DEAD);
}