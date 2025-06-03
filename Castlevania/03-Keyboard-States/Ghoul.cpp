#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Ghoul.h"
#include "Whip.h"
#include "Enemy.h"
#include <cstdlib>

CGhoul::CGhoul()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(GHOUL_ANI_SET_ID));
	this->SetState(GHOUL_STATE_IDLE);
	this->SetAniId(ANI_ID_GHOUL_IDLE);
	this->ay = GRAVITY;

	health = 1;
}
void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!(isDead() || isActived()))
	{
		CSimon* player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
		if (this->CheckEnemyCanActive(player)) ActiveEnemy();
	}
	if (this->isDead())
	{
		if (GetTickCount64() - startDeathTime >= ENEMY_DEAD_TIME)
			isDeleted = true;
	}
	else if (this->health <= 0)
	{
		this->SetState(GHOUL_STATE_DEAD);
		this->NormalEnemyDead(ENEMY_DEAD_TIME);
	}
	else
	{
		if (this->state == GHOUL_STATE_WALK)
			vx = GHOUL_WALKING_SPEED * nx;
		vy += ay * dt;
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}

void CGhoul::Render()
{
	if(!this->isDead())
		animation_set->at(this->GetAniId())->Render(x, y, nx, width, height);
}

void CGhoul::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CGhoul::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj)) return;
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0.0f;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0.0f;
	}
}

void CGhoul::SetState(int state)
{
	switch (state)
	{
	case GHOUL_STATE_IDLE:
		this->SetAniId(ANI_ID_GHOUL_IDLE);
		break;
	case GHOUL_STATE_WALK:
		this->SetAniId(ANI_ID_GHOUL_WALK);
		break;
	case GHOUL_STATE_DEAD:
		break;
	}
	this->state = state;
}

int CGhoul::IsCollidable()
{
	return !(this->isDead());
}
void CGhoul::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->SetDirectionX(extra_settings[0]);
}
int CGhoul::CheckEnemyCanActive(CSimon* simon)
{
	float x = simon->GetX();
	if (abs(x - this->x) <= GHOUL_RANGE_ACTIVE) return 1;
	return 0;
}
void CGhoul::ActiveEnemy()
{
	CEnemy::ActiveEnemy();
	CSimon* player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	if (player->GetX() < this->x) this->nx = -1;
	else this->nx = 1;
	this->SetState(GHOUL_STATE_WALK);
	this->SetSpeed(GHOUL_WALKING_SPEED * nx, 0);
}
int CGhoul::isDead()
{
	return (this->state == GHOUL_STATE_DEAD);
}