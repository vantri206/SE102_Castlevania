#include "CTreeObject.h"

CTreeObject::CTreeObject(LPGAMEOBJECT target)
{
    // Gán đối tượng gốc
    this->target = target;

    // Lấy vị trí và kích thước của đối tượng
    target->GetPosition(x, y);
    target->GetSize(width, height);
}

bool CTreeObject::Intersects(float x0, float y0, float x1, float y1)
{
    // Bounding box của object
    float left = x - width / 2;
    float right = x + width / 2;
    float bottom = y - height / 2;
    float top = y + height / 2;

    // Kiểm tra giao nhau giữa bounding box object và node
    return !(right < x0 || left > x1 || top < y0 || bottom > y1);
}
