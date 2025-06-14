#include "Wall.h"

CWall::CWall()
{

}
void CWall::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 1)
		this->SetSize(extra_settings[0], extra_settings[1]);
	if (extra_settings.size() > 2)
		if (extra_settings[2] == 0) active = 0;
}