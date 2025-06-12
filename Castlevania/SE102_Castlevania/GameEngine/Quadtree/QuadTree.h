#pragma once

#include "QNode.h"
#include "unordered_set"

#define MAX_DEPTH 5
#define MIN_NODE_SIZE 256 

class QuadTree
{
private:
    QNode* root;

    void Subdivide(QNode* node, int depth);
    void Retrieve(QNode* node, RECT camRect, std::unordered_set<LPGAMEOBJECT>& result);
    void PrintNode(QNode* node, int level);
    bool RemoveObj(QNode* node, CGameObject* Obj);


    int mapWidth, mapHeight;
public:
    QuadTree(int mapWidth, int mapHeight);
    void PrintTree();
    ~QuadTree();

    void Insert(LPGAMEOBJECT obj);
    void Remove(LPGAMEOBJECT obj);
    void insertNode(QNode* node, CTreeObject* treeObj, int depth);
    void Update(vector<LPGAMEOBJECT>& Objects);

    std::vector<LPGAMEOBJECT> GetObjectsInView(RECT cam);
    std::vector<LPGAMEOBJECT> GetAllObjects();
};
