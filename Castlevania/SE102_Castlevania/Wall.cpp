#include "Wall.h"

CWall::CWall()
{

}
void CWall::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 1)
		this->SetSize(extra_settings[0], extra_settings[1]);
}