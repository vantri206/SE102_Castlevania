#pragma once
#include "GameObject.h"
#include "Enemy.h"

#include "Animation.h"
#include "Animations.h"

#include "GameDefine.h"
#include "debug.h"

#define GHOUL_WALKING_SPEED	0.15f

#define WHIP_STATE_ATTACK 0

#define ANI_ID_WHIP_ATTACK 0

#define WHIP_SIZE 0.35f
class CWhip : public CGameObject
{
protected:
public:
	CWhip()
	{
		vx = 0;
		vy = 0;
		nx = 1;
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(WHIP_ANI_SET_ID));
	}
	void Update(DWORD dt) {}
	void Render()
	{
		animation_set->at(ANI_ID_WHIP_ATTACK)->Render(x, y, nx, WHIP_SIZE);
	}
	void SetState(int state) {}
	void OnNoCollision(DWORD dt) {}
	void OnCollisionWith(LPCOLLISIONEVENT e) {}
	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; };
};