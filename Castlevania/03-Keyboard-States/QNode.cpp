#include "QNode.h"

QNode::QNode(int x0, int y0, int x1, int y1)
{
    // Khởi tạo vùng không gian node từ (x0, y0) đến (x1, y1)
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;

    // Khởi tạo 4 node con là nullptr (sẽ tạo khi phân tách)
    lt = rt = lb = rb = nullptr;
}

QNode::~QNode()
{
    // Giải phóng bộ nhớ các node con
    delete lt;
    delete rt;
    delete lb;
    delete rb;

    // Xóa danh sách đối tượng trong node
    objects.clear();
}

bool QNode::IsLeaf()
{
    // Kiểm tra node có phải là node lá (không có node con)
    return lt == nullptr && rt == nullptr && lb == nullptr && rb == nullptr;
}

int QNode::Width()
{
    // Tính chiều rộng của node
    return x1 - x0;
}

int QNode::Height()
{
    // Tính chiều cao của node
    return y1 - y0;
}
