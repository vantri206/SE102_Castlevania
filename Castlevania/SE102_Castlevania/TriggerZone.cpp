#include "TriggerZone.h"


CTriggerZone::CTriggerZone()
{

}

void CTriggerZone::Trigger()
{
	if (spawnObjectId != -1)
	{
		CGameObject* dropObj = CGameObject::CreateObject(spawnObjectId, spawnObjectId, spawnObjectExtraSettings);
		if (dropObj != nullptr)
		{
			dropObj->SetPosition(this->spawnX, this->spawnY);
			CGame::GetInstance()->GetCurrentScene()->AddObject(dropObj);
			CGame::GetInstance()->GetCurrentScene()->AddHiddenObject(dropObj);
		}
	}
	this->Delete();
}

void CTriggerZone::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 5)
	{
		this->width = extra_settings[0];
		this->height = extra_settings[1];
		this->spawnObjectId = extra_settings[2];
		this->spawnX = extra_settings[3];
		this->spawnY = extra_settings[4];
	}
	if (extra_settings.size() > 6)
	{
		this->spawnObjectExtraSettings = vector<int>(extra_settings.begin() + 5, extra_settings.end());
	}
}
