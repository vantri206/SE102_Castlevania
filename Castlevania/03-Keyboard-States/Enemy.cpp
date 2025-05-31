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
	this->SetSpeed(0, 0);
	CScene* currentscene = CGame::GetInstance()->GetCurrentScene();
	CDeadEffect* deadEffect = new CDeadEffect(this->x, this->y, duration);
	currentscene->AddEffect(static_cast<CGameEffect*>(deadEffect));
}


