#pragma once
#include "GameObject.h"

class CTreeObject
{
public:
    LPGAMEOBJECT target;

    CTreeObject(LPGAMEOBJECT target);

    bool Intersects(float x0, float y0, float x1, float y1);
};
