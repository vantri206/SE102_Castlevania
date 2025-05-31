#include <algorithm>
#include "debug.h"
#include "Ghoul.h"
#include "Whip.h"
#include <cstdlib>

CGhoul::CGhoul()
{
	vx = vy = 0.0f;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(GHOUL_ANI_SET_ID));
	this->SetState(GHOUL_STATE_IDLE);
	this->SetAniId(ANI_ID_GHOUL_IDLE);

	health = 1;
}
void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDead())
	{
		if (GetTickCount64() - startDeathTime >= GHOUL_DEATH_TIME)
			isDeleted = true;
	}
	else if (this->health <= 0)
	{
		this->SetState(GHOUL_STATE_DEAD);
		this->NormalEnemyDead(GHOUL_DEATH_TIME);
	}
	else
	{
		vx += ax * dt;
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
bool CGhoul::isDead()
{
	return (this->state == GHOUL_STATE_DEAD);
}