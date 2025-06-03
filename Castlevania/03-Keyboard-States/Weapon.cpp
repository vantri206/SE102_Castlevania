#include "Weapon.h"
#include "Enemy.h"
#include "BreakableObject.h"
#include "Camera.h"

int CWeapon::CanCollisionWithObj(LPGAMEOBJECT objDests)
{
	if (dynamic_cast<CEnemy*>(objDests))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(objDests);
		if (enemy->isDead())
			return 0;
	}
	if (dynamic_cast<CBreakableObject*>(objDests))
	{
		CBreakableObject* breakableObj = dynamic_cast<CBreakableObject*>(objDests);
		if (breakableObj->isInDestroyed())
			return 0;
	}
	return 1;
}
int CWeapon::isInViewport()
{
	return CCamera::GetInstance()->IsInCamera(this);
}