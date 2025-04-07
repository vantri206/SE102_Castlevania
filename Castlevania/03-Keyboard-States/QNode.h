#pragma once
#include <vector>
#include "CTreeObject.h"

class QNode
{
public:
    int x0, y0, x1, y1;
    std::vector<CTreeObject*> objects;

    QNode* lt;
    QNode* rt;
    QNode* lb;
    QNode* rb;

    QNode(int x0, int y0, int x1, int y1);
    ~QNode();

    bool IsLeaf();
    int Width();
    int Height();
};
