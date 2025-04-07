#include "QuadTree.h"

QuadTree::QuadTree(int mapWidth, int mapHeight, std::vector<LPGAMEOBJECT>& gameObjects)
{
    // Tìm bounding square
    int size = max(mapWidth, mapHeight);
    int bound = 1;
    while (bound < size) bound *= 2;
    root = new QNode(0, 0, bound, bound);

    for (auto& obj : gameObjects)
    {
        root->objects.push_back(new CTreeObject(obj));
    }

    Subdivide(root, 1);
}

QuadTree::~QuadTree()
{
    delete root;
}

void QuadTree::Subdivide(QNode* node, int depth)
{
    if (depth > MAX_DEPTH || node->Width() <= MIN_NODE_SIZE || node->Height() <= MIN_NODE_SIZE || node->objects.size() <= 1)
        return;

    int midX = (node->x0 + node->x1) / 2;
    int midY = (node->y0 + node->y1) / 2;

    node->lt = new QNode(node->x0, node->y0, midX, midY);
    node->rt = new QNode(midX, node->y0, node->x1, midY);
    node->lb = new QNode(node->x0, midY, midX, node->y1);
    node->rb = new QNode(midX, midY, node->x1, node->y1);

    for (CTreeObject* obj : node->objects)
    {
        Clip(obj, node->lt);
        Clip(obj, node->rt);
        Clip(obj, node->lb);
        Clip(obj, node->rb);
    }

    node->objects.clear();

    Subdivide(node->lt, depth + 1);
    Subdivide(node->rt, depth + 1);
    Subdivide(node->lb, depth + 1);
    Subdivide(node->rb, depth + 1);
}

void QuadTree::Clip(CTreeObject* obj, QNode* node)
{
    if (obj->Intersects(node->x0, node->y0, node->x1, node->y1))
    {
        node->objects.push_back(obj);
    }
}

void QuadTree::Retrieve(QNode* node, RECT camRect, std::vector<LPGAMEOBJECT>& result)
{
    if (node->x1 < camRect.left || node->x0 > camRect.right ||
        node->y1 < camRect.top || node->y0 > camRect.bottom)
        return;

    for (CTreeObject* obj : node->objects)
    {
        result.push_back(obj->target);
    }

    if (!node->IsLeaf())
    {
        Retrieve(node->lt, camRect, result);
        Retrieve(node->rt, camRect, result);
        Retrieve(node->lb, camRect, result);
        Retrieve(node->rb, camRect, result);
    }
}

std::vector<LPGAMEOBJECT> QuadTree::GetObjectsInView(RECT cam)
{
    std::vector<LPGAMEOBJECT> result;
    Retrieve(root, cam, result);
    return result;
}
/*
Cách dùng trong PlayScene.cpp
#include "QuadTree.h"

QuadTree* quadtree;

void CPlayScene::Load()
{
    ...
    quadtree = new QuadTree(mapWidth, mapHeight, allObjects);
}

void CPlayScene::Update(DWORD dt)
{
    RECT cam = CGame::GetInstance()->GetCamRect();
    auto activeObjects = quadtree->GetObjectsInView(cam);

    for (auto obj : activeObjects)
        obj->Update(dt, &activeObjects);
}

*/