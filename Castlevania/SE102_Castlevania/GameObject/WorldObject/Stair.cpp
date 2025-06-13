#pragma once

#include "Stair.h"
#include "Simon.h"

CStair::CStair()
{
	width = STAIR_WIDTH;
	height = STAIR_HEIGHT;
}

void CStair::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 0)
	{
		stair_direction = extra_settings[0];
		horizontal_direction = extra_settings[1];
	}
}

int CStair::GetStairDirection()
{
	return stair_direction;
}

int CStair::GetHorizontalDirection()
{
	return horizontal_direction;
}

CStair::~CStair()
{
	CSimon* player = CSceneManager::GetInstance()->GetPlayer();
	if (this == player->GetNearbyStair())
		player->SetNearbyStair(nullptr);
}