#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Ghoul.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "debug.h"
#include "Collision.h"

#define GHOUL_WALKING_SPEED	0.15f

#define WHIP_STATE_ATTACK 0

#define ANI_ID_WHIP_ATTACK 0

#define WHIP_SIZE 0.35f

#define WHIP_BBOX_WIDTH 24
#define WHIP_BBOX_HEIGHT 16


class CWhip : public CGameObject
{
protected:
	float width;
	float height;
	bool isFinished;
public:
	CWhip()
	{
		vx = 0;
		vy = 0;
		nx = 1;
		width = WHIP_BBOX_WIDTH;
		height = WHIP_BBOX_HEIGHT;
		isFinished = false;
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(WHIP_ANI_SET_ID));
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		if (isFinished)
		{
			left = top = right = bottom = 0;
			return;
		}
		left = x - width/2;
		right = x + width/2;
		top = y - height/2;
		bottom = y + height/2;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (!coObjects || isFinished) return;

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CGhoul*>(obj))
			{
				float left_a, top_a, right_a, bottom_a;
				float left_b, top_b, right_b, bottom_b;

				this->GetBoundingBox(left_a, top_a, right_a, bottom_a);
				obj->GetBoundingBox(left_b, top_b, right_b, bottom_b);

				if (!(right_a < left_b || left_a > right_b || top_a > bottom_b || bottom_a < top_b))
				{
					CGhoul* ghoul = dynamic_cast<CGhoul*>(obj);
					ghoul->SetState(GHOUL_STATE_DIE);
					DebugOut(L"[INFO] WhipHitGhoul\n");
				}
			}
		}
	}

	void OnNoCollision(DWORD dt) {}

	void OnCollisionWith(LPCOLLISIONEVENT e) {}

	void Render()
	{
		if (!isFinished)
		{
			float render_x = x - width/2;
			float render_y = y - height/2;
			animation_set->at(ANI_ID_WHIP_ATTACK)->Render(render_x, render_y, nx, WHIP_SIZE);
		}
	}

	void SetState(int state) {}
	int IsCollidable() { return !isFinished; }
	int IsBlocking() { return 0; }
	void SetFinished(bool finished) { isFinished = finished; }
	bool IsFinished() { return isFinished; }
	void SetDirectionX(int direction) { this->nx = direction; }
};