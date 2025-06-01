#include "CTreeObject.h"

CTreeObject::CTreeObject(LPGAMEOBJECT target)
{
    this->target = target;
}

bool CTreeObject::Intersects(float x0, float y0, float x1, float y1)
{
    float x, y, width, height;
    target->GetPosition(x, y);
    target->GetSize(width, height);
    float left = x - width / 2;
    float right = x + width / 2;
    float bottom = y - height / 2;
    float top = y + height / 2;
    return !(right < x0 || left > x1 || top < y0 || bottom > y1);
}