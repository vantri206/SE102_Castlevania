#include "Whip.h"
#include "Simon.h"
#include "BreakableObject.h"

CWhip::CWhip(CSimon* simon)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(WHIP_ANI_SET_ID));
	this->SetState(WHIP_STATE_ATTACK);
	owner = simon;
	damage = 1;
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
		width = whipFrameWidths[currentFrameIndex];
		height = whipFrameHeights[currentFrameIndex];
	}
}

void CWhip::UpdatePostition(int currentFrameIndex)
{
	float x, y;
	int owner_dirx;
	owner->GetPosition(x, y);
	owner_dirx = owner->GetDirectionX();

	switch (currentFrameIndex)
	{
	case 0:
		this->SetPosition(x - width * owner_dirx, y - 4);
		break;
	case 1:
		this->SetPosition(x - (width - 5) * owner_dirx, y + 3);
		break;
	case 2:
		this->SetPosition(x + (width - 5) * owner_dirx, y + 7);
		break;
	}
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
	animation_set->at(ANI_ID_WHIP_ATTACK)->Render(x, y, nx, width, height);
	this->RenderBoundingBox();
}

int CWhip::IsCollidable()
{
	CAnimation* ani = animation_set->at(ani_id);
	int currentFrameIndex = ani->GetCurrentFrameIndex();
	if (currentFrameIndex == 2) return 1;
	return 0;
}
