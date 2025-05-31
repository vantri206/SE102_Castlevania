#include "Brick.h"

CBrick::CBrick()
{
}
int CBrick::IsDirectionColliable(int nx, int ny)
{
	if (ny > 0) return 1;
	return 0;
}