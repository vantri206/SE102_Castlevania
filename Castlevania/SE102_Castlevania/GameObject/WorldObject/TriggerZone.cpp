#include "TriggerZone.h"
#include "Enemy.h"

CTriggerZone::CTriggerZone()
{

}

void CTriggerZone::Trigger()
{
	if (typeTriggerZone == TRIGGER_ZONE_ITEM)
	{
		if (spawnObjectId != -1)
		{
			CGameObject* dropObj = nullptr;
			dropObj = CGameObject::CreateObject(spawnObjectId, spawnObjectId, spawnObjectExtraSettings);
			if (dropObj != nullptr)
			{
				dropObj->SetPosition(this->spawnX, this->spawnY);
				CGame::GetInstance()->GetCurrentPlayScene()->AddObject(dropObj);
				CGame::GetInstance()->GetCurrentPlayScene()->AddHiddenObject(dropObj);
				dropObj->StartSpawning();
			}
		}
	}
	else
	{
		CPlayScene* playscene = CGame::GetInstance()->GetCurrentPlayScene();
		vector<CGameObject*> objects = playscene->GetAllObjects();
		for (auto obj : objects)
		{
			if (obj->GetId() == enemyTriggerId)
			{
				CEnemy* enemy = dynamic_cast<CEnemy*>(obj);
				enemy->ActiveEnemy();

			}
		}
	}
	this->Delete();
}

void CTriggerZone::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		typeTriggerZone = extra_settings[0];
	switch (typeTriggerZone)
	{
	case TRIGGER_ZONE_ITEM:
		if (extra_settings.size() > 5)
		{
			this->width = extra_settings[1];
			this->height = extra_settings[2];
			this->spawnObjectId = extra_settings[3];
			this->spawnX = extra_settings[4];
			this->spawnY = extra_settings[5];
		}
		if (extra_settings.size() > 6)
		{
			this->spawnObjectExtraSettings = vector<int>(extra_settings.begin() + 5, extra_settings.end());
		}
		break;
		case TRIGGER_ZONE_ENEMY:
		if (extra_settings.size() > 3)
		{
			this->width = extra_settings[1];
			this->height = extra_settings[2];
			this->enemyTriggerId = extra_settings[3];
		}
		break;
	}
}
