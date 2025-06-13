#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#include "Item.h"
#include "GameSetting.h"

#define ID_ANI_HOLYCROSS 0

class CHolyCross : public CItem
{
public:
	CHolyCross();
	void TriggerCrossEffect();
};
