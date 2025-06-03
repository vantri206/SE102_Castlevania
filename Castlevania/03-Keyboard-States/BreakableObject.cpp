#include "BreakableObject.h"
#include "DeadEffect.h"
#include "debug.h"

void CBreakableObject::OnHit()
{
	this->TriggerDestroyedEffect(BREAKABLEOBJCET_DESTROYED_TIME);
	this->startDestroyedTime = GetTickCount64();
}

void CBreakableObject::Update(DWORD dt, vector<CGameObject*>* coObjects)
{
	if (this->isInDestroyed() && GetTickCount64() - startDestroyedTime >= BREAKABLEOBJCET_DESTROYED_TIME)
	{
		this->Delete();
	}
}
void CBreakableObject::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
		this->SetItemDrop(extra_settings[0]);
}

void CBreakableObject::SetItemDrop(int itemid)
{ 
	this->itemdropId = itemid; 
}

void CBreakableObject::TriggerDestroyedEffect(int duration)
{
	CScene* currentscene = CGame::GetInstance()->GetCurrentScene();
	CDeadEffect* deadEffect = new CDeadEffect(this->x, this->y, duration);
	currentscene->AddEffect(static_cast<CGameEffect*>(deadEffect));
}

int CBreakableObject::isInDestroyed()
{
	return (startDestroyedTime != -1);
}