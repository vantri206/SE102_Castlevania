#include "HolyCross.h"
#include <FlashEffect.h>
#include <Enemy.h>

CHolyCross::CHolyCross()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(HOLYCROSS_ANI_SET_ID));
	this->SetAniId(ID_ANI_HOLYCROSS);
    ay = DEFAULT_GRAVITY;
    this->SetSize(HOLYCROSS_WIDTH, HOLYCROSS_HEIGHT);
}

void CHolyCross::TriggerCrossEffect()
{
    CPlayScene* currentPlayScene = CGame::GetInstance()->GetCurrentPlayScene();
    if (!currentPlayScene) return;

    auto objects = currentPlayScene->GetAllObjects();
    for (auto obj : objects)
        if(CCamera::GetInstance()->IsInCamera(obj))
        {
            CEnemy* enemy = dynamic_cast<CEnemy*>(obj);
            if (!enemy) continue;
            if (!(enemy->isDead() || enemy->IsDeleted()))
            {
                enemy->TakenDamage(999);
            }
        }
	CFlashEffect* flasheffect = new CFlashEffect();
    currentPlayScene->AddEffect(flasheffect);
}
