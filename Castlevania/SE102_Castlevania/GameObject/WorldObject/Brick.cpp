#include "Brick.h"

CBrick::CBrick()
{

}
int CBrick::IsDirectionColliable(int nx, int ny)
{
	if (nx != 0 || ny > 0) return 1;
	return 0;
}
void CBrick::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 1)
		this->SetSize(extra_settings[0], extra_settings[1]);
}