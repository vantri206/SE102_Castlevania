#pragma once

#include "GameObject.h"
#include "debug.h"
#include "Torch.h"
#include "Candle.h"
#include "Ghoul.h"
#include "Panther.h"
#include "FishMan.h"
#include "Brick.h"
#include "Portal.h"
#include "Stair.h"
#include "MorningStar.h"
#include "Wall.h"
#include "BigHeart.h"
#include "SmallHeart.h"
#include "SubWeaponItem.h"
#include "BreakableBrick.h"
#include "WaterDeadZone.h"
#include "MoneyBag.h"
#include "TriggerZone.h"
#include "SplashEffect.h"
#include "Bat.h"
#include "EnemySpawn.h"
#include "Gate.h"
#include "PhantomBat.h"

#define ID_TEX_BBOX 999

CGameObject* CGameObject::CreateObject(int objectId, int objectType, vector<int> extra_settings)
{
	CGameObject* obj = nullptr;
	switch (objectType)
	{
	case TORCH:
		obj = new CTorch();
		break;
	case CANDLE:
		obj = new CCandle();
		break;

	case BRICK:
		obj = new CBrick();
		break;
	case PORTAL:
		obj = new CPortal();
		break;
	case STAIR:
		obj = new CStair();
		break;
	case MORNINGSTAR:
		obj = new CMorningStar();
		break;
	case BIGHEART:
		obj = new CBigHeart();
		break;
	case SMALLHEART:
		obj = new CSmallHeart();
		break;
	case SUBWEAPONITEM:
		obj = new CSubWeaponItem();
		break;
	case MONEYBAG:
		obj = new CMoneyBag();
		break;
	case TRIGGERZONE:
		obj = new CTriggerZone();
		break;
	case BREAKABLEBRICK:
		obj = new CBreakableBrick();
		break;
	case WALL:
		obj = new CWall();
		break;
	case WATERDEADZONE:
		obj = new CWaterDeadZone();
		break;
	case GATEPORTAL:
		obj = new CGate();
		break;
	case GHOUL:
	case PANTHER:
	case BAT:
	case FISHMAN:
		obj = new CEnemySpawn();
		break;
	case PHANTOMBAT:
		obj = new CPhantomBat();
		break;
	default:
		DebugOut(L"[ERROR] Unknown object type: %d\n", objectType);
		break;
	}
	if (obj)
	{
		obj->SetId(objectId);
		obj->SetType(objectType);
		obj->LoadExtraSetting(extra_settings);
	}
	return obj;
}

void CGameObject::TriggerSplashEffect(float x, float y)
{
	DebugOut(L"trigger\n");
	vector <CSplashEffect*>splasheffects;
	splasheffects.push_back(new CSplashEffect(x, y, -0.025f, 0.15f, SPLASHEFFECT_GRAVITY));
	splasheffects.push_back(new CSplashEffect(x, y, 0, 0.2f, SPLASHEFFECT_GRAVITY));
	splasheffects.push_back(new CSplashEffect(x, y, 0.025f, 0.15f, SPLASHEFFECT_GRAVITY));
	for (auto splasheffect : splasheffects)
		CGame::GetInstance()->GetCurrentPlayScene()->AddEffect(splasheffect);
}

CGameObject::CGameObject()
{
	x = y = 0;
	width = height = 0;
	vx = vy = 0;
	nx = ny = 1;
	state = -1;
	isDeleted = false;
}
void CGameObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y + height / 2;
	r = x + width / 2;
	b = y - height / 2;
}
void CGameObject::RenderBoundingBox()
{
	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);
	CGame::GetInstance()->DrawBoundingBox(l, t, r, b);
}
int CGameObject::isInSceneViewport()
{
	CPlayScene* playscene = CGame::GetInstance()->GetCurrentPlayScene();
	if (playscene)
	{
		int width = playscene->GetCurrentMapWidth();
		int height = playscene->GetCurrentMapHeight();
		if (this->x >= 0 && this->x <= width && this->y >= 0 && this->y <= height)
		{
			return 1;
		}
	}
	return 0;
}
CGameObject::~CGameObject()
{

}