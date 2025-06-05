#pragma once

#include "GameObject.h"
#include "debug.h"
#include "Torch.h"
#include "Candle.h"
#include "Ghoul.h"
#include "Panther.h"
#include "Brick.h"
#include "Portal.h"
#include "Stair.h"
#include "MorningStar.h"
#include "BigHeart.h"
#include "SmallHeart.h"
#include "SubWeaponItem.h"
#include "MoneyBag.h"
#include "TriggerZone.h"

#define ID_TEX_BBOX 999

CGameObject* CGameObject::CreateObject(int objectId, int objectType, vector<int> extra_settings)
{
	CGameObject* obj = NULL;
	switch (objectType)
	{
	case TORCH:
		obj = new CTorch();
		break;
	case CANDLE:
		obj = new CCandle();
		break;
	case GHOUL:
		obj = new CGhoul();
		break;
	case PANTHER:
		obj = new CPanther();
		break;
	case BRICK:
		obj = new CBrick();
		break;
	case PORTAL:
		obj = new CBrick();
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
	case TRIGGERZONE:
		obj = new CTriggerZone();
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
CGameObject::~CGameObject()
{

}