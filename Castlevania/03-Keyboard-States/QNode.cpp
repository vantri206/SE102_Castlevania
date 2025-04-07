#include "QNode.h"

QNode::QNode(int x0, int y0, int x1, int y1)
{
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;

    lt = rt = lb = rb = nullptr;
}

QNode::~QNode()
{
    delete lt;
    delete rt;
    delete lb;
    delete rb;

    objects.clear();
}

bool QNode::IsLeaf()
{
    return lt == nullptr && rt == nullptr && lb == nullptr && rb == nullptr;
}

int QNode::Width()
{
    return x1 - x0;
}

int QNode::Height()
{
    return y1 - y0;
}
