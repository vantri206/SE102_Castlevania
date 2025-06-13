#pragma once
#include <algorithm>
#include "Simon.h"
#include "Camera.h"
#include "Enemy.h"
#include "Brick.h"
#include "Candle.h"
#include "Whip.h"
#include "SmallHeart.h"
#include "BigHeart.h"
#include "MoneyBag.h"
#include "MorningStar.h"
#include "SubWeaponItem.h"
#include "SimonAttack.h"
#include "SimonPowerUp.h"
#include "SimonJump.h"
#include "SimonSit.h"
#include "BreakableBrick.h"
#include "Bat.h"
#include "Fireball.h"
#include "SimonDie.h"
#include <SimonFloat.h>

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	if (GetTickCount64() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
		FinishedUntouchable();
	if (GetTickCount64() - invisible_start > SIMON_INVISIBLE_TIME)
		FinishedInvisible();

	this->CheckStairNearby(coObjects);

	CCollision::GetInstance()->Process(this, dt, coObjects);

	currentState->Update(dt);

	this->UpdateWeapon(dt, coObjects);

	int mapwidth = 0, mapheight = 0;
	CPlayScene* currentPlayScene = CGame::GetInstance()->GetCurrentPlayScene();
	if (currentPlayScene)
	{
		mapwidth = currentPlayScene->GetCurrentMapWidth();
		mapheight = currentPlayScene->GetCurrentMapHeight();
	}

	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);

    if (x < 0) x = 0;
    else if (x > mapwidth) x = (float)mapwidth;

    if (y < 0) y = 0;
    else if (y > mapheight) y = (float)mapheight;

	CCamera::GetInstance()->Update(dt, this, mapwidth, mapheight);
}
void CSimon::OnNoCollision(DWORD dt)
{
	currentState->OnNoCollision(dt);
}
void CSimon::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CSimon*>(e->obj)) return;
	currentState->OnCollisionWith(e);
}

void CSimon::OnCollisionWithEnemy(CEnemy* enemy)
{
	this->TakenDamage(enemy->GetAttack());
	this->SetState(new CSimonHurt(this));
	this->StartUntouchable();
	if (dynamic_cast<CBat*>(enemy))
		enemy->TakenDamage(999);
}
void CSimon::OnCollisionWithEnemyOnStair(CEnemy* enemy)
{
	this->TakenDamage(enemy->GetAttack());
	this->StartUntouchable();
	if (dynamic_cast<CBat*>(enemy))
		enemy->TakenDamage(999);
}
void CSimon::OnCollisionWithItem(CItem* item)
{
	switch (item->GetType())
	{
		case BIGHEART:
		{
			CBigHeart* bigheart = dynamic_cast<CBigHeart*>(item);
			this->addHeart(bigheart->getHeartValue());
			break;
		}
		case SMALLHEART:
		{
			CSmallHeart* smallheart = dynamic_cast<CSmallHeart*>(item);
			this->addHeart(smallheart->getHeartValue());
			break;
		}
		case MORNINGSTAR:
		{
			this->UpgradeWeapon();
			this->SetState(new CSimonPowerUp(this));
			break;
		}
		case SUBWEAPONITEM:
		{
			CSubWeaponItem* subweaponitem = dynamic_cast<CSubWeaponItem*>(item);
			this->SetSubWeapon(subweaponitem->GetSubWeaponType());
			break;
		}
		case MONEYBAG:
		{
			CMoneyBag* moneybag = dynamic_cast<CMoneyBag*>(item);
			int score = moneybag->GetScore();
			CHUD* hud = CSceneManager::GetInstance()->GetHUD();
			hud->SetScore(hud->GetScore() + score);
			break;
		}
	}
	item->Delete();
}
void CSimon::OnCollisionWithBullet(CFireball* fireball)
{
	this->TakenDamage(FIREBALL_DAMAGE);
	this->SetState(new CSimonHurt(this));
	this->StartUntouchable();
	fireball->Delete();
}

void CSimon::UpgradeWeapon()
{
	if (whipLevel < SIMON_MAX_WHIP_LEVEL)
		whipLevel++;
}

void CSimon::UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (currentWeapon != nullptr)
	{
		currentWeapon->Update(dt, coObjects);
	}
	if (activeSubWeaponList.size() > 0)
	for (int i = 0; i < activeSubWeaponList.size(); )
	{
		CWeapon* subweapon = activeSubWeaponList[i];
		subweapon->Update(dt, coObjects);
		if (subweapon->IsDeleted())
		{
			delete subweapon;
			activeSubWeaponList.erase(activeSubWeaponList.begin() + i);
		}
		else i++;
	}
}

int CSimon::CanUseSubWeapon()
{
	return (currentSubWeaponType != -1 && activeSubWeaponList.size() < subWeaponLimit && heartCount > 0);
}

void CSimon::AddSubWeapon(CWeapon* subweapon)
{
	activeSubWeaponList.push_back(subweapon);
}

void CSimon::RemoveAllSubWeapons()
{
	if(activeSubWeaponList.size() > 0)
	for (int i = 0; i < activeSubWeaponList.size(); ++i)
	{
		CWeapon* subweapon = activeSubWeaponList[i];
		delete subweapon;
	}
	activeSubWeaponList.clear();
}

void CSimon::RenderSubWeapons()
{
	if (activeSubWeaponList.size() > 0)
	for (int i = 0; i < activeSubWeaponList.size(); ++i)
	{
		CWeapon* subweapon = activeSubWeaponList[i];
		subweapon->Render();
		subweapon->RenderBoundingBox();
	}
}

void CSimon::TakenDamage(int damage)
{
	health -= damage;
}

void CSimon::UpdateMoving(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CSimon::OnKeyDown(int keyCode)
{
	currentState->KeyDownHandle(keyCode);
}

void CSimon::OnKeyUp(int keyCode)
{
	currentState->KeyUpHandle(keyCode);
}

void CSimon::SetState(CSimonState* state) 
{
	currentState.reset(state);
	animation_set->at(ani_id)->Reset();
}

CSimonState* CSimon::GetSimonState()
{
	return currentState.get();
}

void CSimon::StartDrowning()
{
	this->SetState(new CSimonDie(this));
	isDrowning = 1;
}

void CSimon::Render()
{
	if (isDrowning) return;
	if (untouchable)					
	{
		DWORD now = GetTickCount64();
		if ((now / SIMON_BLINK_TIME) % 2 == 0)									
		{
			animation_set->at(ani_id)->Render(x, y, nx, width, height);
		}
	}
	else animation_set->at(ani_id)->Render(x, y, nx, width, height);
	currentState->Render();
	this->RenderSubWeapons();
}

void CSimon::CheckStairNearby(vector<LPGAMEOBJECT>* coObjects)
{
	this->nearbyStair = nullptr;
	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);
	for (int i = 0; i < coObjects->size(); i++)
	{
		CGameObject* obj = coObjects->at(i);
		if (!obj) continue;
		if (obj->IsDeleted()) continue;
		if (dynamic_cast<CStair*>(obj))
		{
			CStair* stair = dynamic_cast<CStair*>(obj);
			float l1, t1, r1, b1;
			stair->GetBoundingBox(l1, t1, r1, b1);
			if (min(r, r1) >= max(l, l1) && min(t, t1) >= max(b, b1))
			{
				this->nearbyStair = stair;
			}
		}
	}
}
bool CSimon::IsNearStairUp()
{
	if (nearbyStair != nullptr)
	{
		if (nearbyStair->GetStairDirection() == UP_STAIR_DIRECTION)
		{
			return true;
		}
	}
	return false;
}
bool CSimon::IsNearStairDown()
{
	if (nearbyStair != nullptr)
	{
		if (nearbyStair->GetStairDirection() == DOWN_STAIR_DIRECTION)
		{
			return true;
		}
	}
	return false;
}

int CSimon::CanCollisionWithObj(LPGAMEOBJECT objDests)
{
	if (dynamic_cast<CBrick*>(objDests))
	{
		if (this->isOnStair) return 0;
		return 1;
	}
	if (dynamic_cast<CEnemy*>(objDests))
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(objDests);
		if (enemy->isDead() || !enemy->isActived() || this->IsUntouchable() || this->IsInvisible())
			return 0;
	}
	return 1;
}
int CSimon::CanOverlapWithObj(LPGAMEOBJECT objDests)
{
	if (dynamic_cast<CBreakableBrick*>(objDests))
	{
		return 0;
	}
	return 1;
}