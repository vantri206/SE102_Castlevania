#include "WaterDeadZone.h"

CWaterDeadZone::CWaterDeadZone()
{

}

void CWaterDeadZone::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 1)
	{
		width = extra_settings[0];
		height = extra_settings[1];
	}
}
