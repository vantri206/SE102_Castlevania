#include "Enemy.h"
#include "Weapon.h"
#include "Effect.h"
#include "DeadEffect.h"
void CEnemy::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
	{
		this->SetDirectionX(extra_settings[0]);
	}
}

void CEnemy::NormalEnemyDead(int duration)
{
	this->startDeathTime = GetTickCount64();
	this->SetPhysical(0.0f, 0.0f, 0.0f, 0.0f);
	this->TriggerNormalEffect(duration);
	this->isActive = 0;
}

void CEnemy::SetPhysical(float vx, float vy, float ax, float ay)
{
	this->vx = vx;
	this->vy = vy;
	this->ax = ax;
	this->ay = ay;
}

void CEnemy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 5;
	t = y + height / 2;
	r = x + width / 5;
	b = y - height / 2;
}

void CEnemy::TriggerNormalEffect(int duration)
{
	CPlayScene* currentPlayScene = CGame::GetInstance()->GetCurrentPlayScene();
	if (currentPlayScene)
	{
		CDeadEffect* deadEffect = new CDeadEffect(this->x, this->y, duration);
		currentPlayScene->AddEffect(static_cast<CGameEffect*>(deadEffect));
	}
}