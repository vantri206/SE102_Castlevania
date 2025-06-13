#include "Portal.h"

CPortal::CPortal()
{
	sceneId = 0;
	sceneEntryId = 0;
}

void CPortal::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 3)
	{
		width = extra_settings[0];
		height = extra_settings[1];
		sceneId = extra_settings[2];
		sceneEntryId = extra_settings[3];
	}
}

void CPortal::ChangeScene()
{
	CSceneManager::GetInstance()->RequestChangeScene(this->sceneId, this->sceneEntryId);
}

void CPortal::Active()
{
	this->ChangeScene();
}
