#include "CTreeObject.h"

CTreeObject::CTreeObject(LPGAMEOBJECT obj)
{
    float l, t, r, b;
    obj->GetBoundingBox(l, t, r, b);

    x1 = (int)l;
    y1 = (int)t;
    x2 = (int)r;
    y2 = (int)b;

    target = obj;
}

bool CTreeObject::Intersects(int left, int top, int right, int bottom)
{
    return !(x2 < left || x1 > right || y2 < top || y1 > bottom);
}
