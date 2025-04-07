#pragma once

#include "QNode.h"

#define MAX_DEPTH 5
#define MIN_NODE_SIZE 256 

class QuadTree
{
private:
    QNode* root;

    void Subdivide(QNode* node, int depth);
    void Clip(CTreeObject* obj, QNode* node);
    void Retrieve(QNode* node, RECT camRect, std::vector<LPGAMEOBJECT>& result);

public:
    QuadTree(int mapWidth, int mapHeight, std::vector<LPGAMEOBJECT>& gameObjects);
    ~QuadTree();

    std::vector<LPGAMEOBJECT> GetObjectsInView(RECT cam);
};
