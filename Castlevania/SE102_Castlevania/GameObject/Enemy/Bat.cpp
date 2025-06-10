#include "debug.h"
#include "Simon.h"
#include "Bat.h"
#include "Enemy.h"
#include "GameSetting.h"

CBat::CBat()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(BAT_ANI_SET_ID));
	this->SetState(BAT_STATE_FLYING);
	this->SetAniId(ANI_ID_BAT_FLYING);
	this->SetSize(BAT_WIDTH, BAT_HEIGHT);

	lastSwingTime = GetTickCount64();
	vx = vy = 0;
	health = BAT_HP;
}
void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDead())
	{
		if (GetTickCount64() - startDeathTime >= ENEMY_DEAD_TIME)
			isDeleted = true;
	}
	else if (!isActived())
	{
		CSimon* player = CSceneManager::GetInstance()->GetPlayer();
		if (this->CheckEnemyCanActive(player)) ActiveEnemy();
	}
	else if (this->health <= 0)
	{
		this->SetState(BAT_STATE_DEAD);
		this->NormalEnemyDead(ENEMY_DEAD_TIME);
	}
	else
	{
		DWORD now = GetTickCount64();
		if (now - lastSwingTime > BAT_SWING_COOLDOWN)
		{
			vy = (-1) * vy;
			lastSwingTime = now;
		}
		x += vx * dt;
		y += vy * dt;
	}

	float camX, camY;

	CPlayScene* playscene = CGame::GetInstance()->GetCurrentPlayScene();
	if (playscene)
	{
		int width = playscene->GetCurrentMapWidth();
		int height = playscene->GetCurrentMapHeight();
		if (!(this->x >= 0 && this->x <= width && this->y >= 0 && this->y <= height))
		{
			isDeleted = true;
		}
	}
}

void CBat::Render()
{
	if (!isActived()) return;
	if (!this->isDead())
		animation_set->at(ani_id)->Render(x, y, nx, width, height);
}

void CBat::OnNoCollision(DWORD dt)
{

}

void CBat::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

int CBat::IsCollidable()
{
	return !(this->isDead() || !this->isActived());
}

void CBat::SetState(int state)
{
	switch (state)
	{
	case BAT_STATE_FLYING:
		this->SetAniId(ANI_ID_BAT_FLYING);
		break;
	case BAT_STATE_DEAD:
		break;
	}
	this->state = state;
}

void CBat::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->SetDirectionX(extra_settings[0]);
}
int CBat::CheckEnemyCanActive(CSimon* simon)
{
	float distance = abs(simon->GetX() - this->x);
	if (distance >= BAT_RANGE_ACTIVE_MIN && distance <= BAT_RANGE_ACTIVE)
		return 1;
	return 0;
}
void CBat::ActiveEnemy()
{
	CEnemy::ActiveEnemy();

	this->SetSpeed(BAT_FLYING_SPEED * nx, BAT_SWING_SPEED);
}
int CBat::isDead()
{
	return (this->state == BAT_STATE_DEAD);
}