#include "QuadTree.h"
#include "debug.h"
#include "Utils.h"
#include "Whip.h"
#include "Ghoul.h"
#include <memory>
#include <unordered_set>

QuadTree::QuadTree(int mapWidth, int mapHeight)
{
    // Tìm kích thước lớn nhất để tạo vùng root là hình vuông
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;
    int size = max(mapWidth, mapHeight);
    int bound = 1;
    while (bound < size) bound *= 2; // Làm tròn lên thành lũy thừa của 2

    // Tạo node gốc từ (0,0) đến (bound,bound)
    root = new QNode(0, 0, bound, bound);

}

QuadTree::~QuadTree()
{
    // Giải phóng root -> gián tiếp giải phóng toàn bộ cây
    delete root;
}

void QuadTree::Insert(LPGAMEOBJECT obj)
{
    CTreeObject* treeObj = new CTreeObject(obj);
    insertNode(root, treeObj, 0);
}


void QuadTree::Remove(LPGAMEOBJECT obj)
{
    RemoveObj(root, obj);
}

bool QuadTree::RemoveObj(QNode* node, CGameObject* obj)
{
    bool isRemoved = false;

    for (auto it = node->objects.begin(); it != node->objects.end();)
    {
        CTreeObject* treeObj = *it;
        if (treeObj->target == obj)
        {
            delete treeObj;
            it = node->objects.erase(it);   //if removed, it = next it
            isRemoved = true;
        }
        else ++it;  //if dont remove, ++it to next it
    }

    if (!node->IsLeaf())
    {
        QNode* children[4] = { node->lt, node->rt, node->lb, node->rb };
        for (QNode* child : children)
        {
            bool res = RemoveObj(child, obj);
            if (!isRemoved) isRemoved = res;
        }
    }
    return isRemoved;
}

void QuadTree::insertNode(QNode* node, CTreeObject* treeObj, int depth)
{
    if (!node->IsLeaf()) {
        QNode* children[4] = { node->lt, node->rt, node->lb, node->rb };
        std::vector<QNode*> intersectNodes;

        for (QNode* child : children) {
            if (treeObj->Intersects(child->x0, child->y0, child->x1, child->y1)) {
                intersectNodes.push_back(child);
            }
        }

        if (intersectNodes.size() == 1) {
            insertNode(intersectNodes[0], treeObj, depth + 1);
            return;
        }
        else                                                                //neu node con khong chua duoc ca obj -> day len cha
        {
            node->objects.push_back(treeObj);
            return;
        }
    }

    node->objects.push_back(treeObj);

    if (depth < MAX_DEPTH && node->Width() > MIN_NODE_SIZE && node->Height() > MIN_NODE_SIZE && node->objects.size() > 4) {
        Subdivide(node, depth + 1);

        auto oldObjects = node->objects;
        node->objects.clear();

        // Insert lại các object sau khi chia node
        for (auto obj : oldObjects) {
            insertNode(node, obj, depth + 1);
        }
    }
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
}

void QuadTree::Retrieve(QNode* node, RECT camRect, std::unordered_set<LPGAMEOBJECT>& res)
{
    // Nếu node nằm ngoài vùng camera thì bỏ qua
    if (node->x1 < camRect.left || node->x0 > camRect.right ||
        node->y1 < camRect.top || node->y0 > camRect.bottom)
        return;

    // Thêm các object trong node vào danh sách kết quả
    for (CTreeObject* obj : node->objects)
    {
        res.insert(obj->target);
    }

    // Nếu node không phải node lá -> tiếp tục kiểm tra các node con
    if (!node->IsLeaf())
    {
        Retrieve(node->lt, camRect, res);
        Retrieve(node->rt, camRect, res);
        Retrieve(node->lb, camRect, res);
        Retrieve(node->rb, camRect, res);
    }
}

vector<LPGAMEOBJECT> QuadTree::GetObjectsInView(RECT cam)
{
    // Trả về danh sách các object trong vùng nhìn thấy (camera)
    std::unordered_set<LPGAMEOBJECT> uniqueRes;
    Retrieve(root, cam, uniqueRes);
    vector<LPGAMEOBJECT> res;
    for (auto obj : uniqueRes)
    {
        res.push_back(obj);
    }
    return res;
}

vector<LPGAMEOBJECT> QuadTree::GetAllObjects()
{
    RECT view;
    view.left = 0;
    view.bottom = 0;
    view.right = mapWidth;
    view.left = mapHeight;
    return this->GetObjectsInView(view);
}

void QuadTree::PrintNode(QNode* node, int level)
{
    if (!node) return;

    string indent(level * 2, ' ');

    DebugOut(L"%sNode (%d,%d)-(%d,%d): ", ToLPCWSTR(indent), node->x0, node->y0, node->x1, node->y1);

    if (node->objects.empty())
    {
        DebugOut(L"[No objects]\n");
    }
    else
    {
        DebugOut(L"Objects: ");
        for (CTreeObject* obj : node->objects)
        {
            if (obj && obj->target)
                DebugOut(L"%d ", obj->target->GetId());
        }
        DebugOut(L"\n");
    }

    // Đệ quy in các node con
    PrintNode(node->lt, level + 1);
    PrintNode(node->rt, level + 1);
    PrintNode(node->lb, level + 1);
    PrintNode(node->rb, level + 1);
}

void QuadTree::PrintTree()
{
    DebugOut(L"===== QuadTree Structure =====\n");
    PrintNode(root, 0);
    DebugOut(L"==============================\n");
}
