#include "Whip.h"
#include "Simon.h"
#include "BreakableObject.h"
#include "SimonSitAttack.h"

CWhip::CWhip(CSimon* simon)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(WHIP_ANI_SET_ID));

	owner = simon;
	damage = 1;
	
	int lv = owner->getWhipLevel();
	this->SetWhipLevel(lv);
}

void CWhip::Update(DWORD dt, vector<CGameObject*>* coObjects)
{
	CAnimation* ani = animation_set->at(ani_id);
	int currentFrameIndex = ani->GetCurrentFrameIndex();
	UpdatePostition(currentFrameIndex);
	UpdateSize(currentFrameIndex);

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CWhip::UpdateSize(int currentFrameIndex)
{
	if (currentFrameIndex >= 0 && currentFrameIndex < 3) 
	{
		width = whipFrameSize[level - 1][currentFrameIndex].frameWidth;
		height = whipFrameSize[level - 1][currentFrameIndex].frameHeight;
	}
}

void CWhip::UpdatePostition(int currentFrameIndex)
{
	float x, y;
	int owner_dirx, simonState;
	owner->GetPosition(x, y);
	owner_dirx = owner->GetDirectionX();
	if(dynamic_cast<CSimonSitAttack*>(owner->GetSimonState()))
		simonState = SITTING;
	else simonState = STANDING;
	this->SetPosition(x - whipOffset[level - 1][simonState][currentFrameIndex].whipoffsetX * owner_dirx,
					  y - whipOffset[level - 1][simonState][currentFrameIndex].whipoffsetY);
}
void CWhip::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		if (enemy)
		{
			if (enemiesTarget.find(enemy) == enemiesTarget.end())
			{
				enemiesTarget.insert(enemy);
				enemy->TakenDamage(this->damage);
			}
		}
	}
	else if (dynamic_cast<CBreakableObject*>(e->obj))
	{
		CBreakableObject* breakableObj = dynamic_cast<CBreakableObject*>(e->obj);
		if (breakableObj) breakableObj->OnHit();
	}
}
void CWhip::Render()
{
	int nx = owner->GetDirectionX();
	animation_set->at(ani_id)->Render(x, y, nx, width, height);
	this->RenderBoundingBox();
}

void CWhip::SetWhipLevel(int level)
{
	this->level = level;
	switch (level)
	{
	case 1:
		state = WHIP_STATE_LV1;
		ani_id = ANI_ID_WHIP_LV1;
		break;
	case 2:
		state = WHIP_STATE_LV2;
		ani_id = ANI_ID_WHIP_LV2;
		break;
	case 3:
		state = WHIP_STATE_LV3;
		ani_id = ANI_ID_WHIP_LV3;
		break;
	default:
		ani_id = ANI_ID_WHIP_LV1;
	}
}

int CWhip::IsCollidable()
{
	CAnimation* ani = animation_set->at(ani_id);
	int currentFrameIndex = ani->GetCurrentFrameIndex();
	if (currentFrameIndex == 2) return 1;
	return 0;
}
