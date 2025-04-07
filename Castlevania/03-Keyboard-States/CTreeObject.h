#pragma once
#include "GameObject.h"

class CTreeObject
{
public:
    int x1, y1, x2, y2;         // bounding box (AABB)
    LPGAMEOBJECT target;        // con trỏ đến object thật trong game

    CTreeObject(LPGAMEOBJECT obj);

    bool Intersects(int left, int top, int right, int bottom);
};
