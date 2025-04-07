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
    void PrintNode(QNode* node, int level);

public:
    QuadTree(int mapWidth, int mapHeight, std::vector<LPGAMEOBJECT>& gameObjects);
    void PrintTree();
    ~QuadTree();

    std::vector<LPGAMEOBJECT> GetObjectsInView(RECT cam);
};
