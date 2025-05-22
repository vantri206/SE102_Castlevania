#include "Enemy.h"
#include "Weapon.h"

void CEnemy::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
	{
		this->SetDirectionX(extra_settings[0]);
	}
}

void CEnemy::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CWeapon*>(e->obj))
	{
		this->Delete();
	}
}
