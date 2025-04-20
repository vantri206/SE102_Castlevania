#include "QuadTree.h"
#include "debug.h"
#include "Utils.h"

QuadTree::QuadTree(int mapWidth, int mapHeight, vector<LPGAMEOBJECT>& gameObjects)
{
    // Tìm kích thước lớn nhất để tạo vùng root là hình vuông
    int size = max(mapWidth, mapHeight);
    int bound = 1;
    while (bound < size) bound *= 2; // Làm tròn lên thành lũy thừa của 2

    // Tạo node gốc từ (0,0) đến (bound,bound)
    root = new QNode(0, 0, bound, bound);

    // Đưa tất cả object vào node gốc dưới dạng CTreeObject
    for (auto& obj : gameObjects)
    {
        root->objects.push_back(new CTreeObject(obj));
    }

    // Bắt đầu chia nhỏ node đệ quy
    Subdivide(root, 1);
}

QuadTree::~QuadTree()
{
    // Giải phóng root -> gián tiếp giải phóng toàn bộ cây
    delete root;
}


void QuadTree::Subdivide(QNode* node, int depth)
{
    // Điều kiện dừng chia: quá độ sâu, kích thước node quá nhỏ, hoặc quá ít object
    if (depth > MAX_DEPTH || node->Width() <= MIN_NODE_SIZE || node->Height() <= MIN_NODE_SIZE || node->objects.size() <= 1)
        return;

    // Tính điểm chia giữa node hiện tại
    int midX = (node->x0 + node->x1) / 2;
    int midY = (node->y0 + node->y1) / 2;

    // Tạo 4 node con
    node->lt = new QNode(node->x0, node->y0, midX, midY); // trên trái
    node->rt = new QNode(midX, node->y0, node->x1, midY); // trên phải
    node->lb = new QNode(node->x0, midY, midX, node->y1); // dưới trái
    node->rb = new QNode(midX, midY, node->x1, node->y1); // dưới phải

    // Gán các object hiện tại vào các node con nếu chúng giao nhau
    for (CTreeObject* obj : node->objects)
    {
        Clip(obj, node->lt);
        Clip(obj, node->rt);
        Clip(obj, node->lb);
        Clip(obj, node->rb);
    }

    // Xóa danh sách object ở node hiện tại (đã chia cho node con)
    node->objects.clear();

    // Đệ quy tiếp cho các node con
    Subdivide(node->lt, depth + 1);
    Subdivide(node->rt, depth + 1);
    Subdivide(node->lb, depth + 1);
    Subdivide(node->rb, depth + 1);
}


void QuadTree::Clip(CTreeObject* obj, QNode* node)
{
    // Nếu object nằm trong vùng của node thì thêm vào
    if (obj->Intersects(node->x0, node->y0, node->x1, node->y1))
    {
        DebugOut(L"[Clip] Object at (%f, %f) clipped to node (%d,%d)-(%d,%d)\n",
            obj->x, obj->y, node->x0, node->y0, node->x1, node->y1);
        node->objects.push_back(obj);
    }
}

void QuadTree::Retrieve(QNode* node, RECT camRect, vector<LPGAMEOBJECT>& result)
{
    // Nếu node nằm ngoài vùng camera thì bỏ qua
    if (node->x1 < camRect.left || node->x0 > camRect.right ||
        node->y1 < camRect.top || node->y0 > camRect.bottom)
        return;

    // Thêm các object trong node vào danh sách kết quả
    for (CTreeObject* obj : node->objects)
    {
        result.push_back(obj->target);
    }

    // Nếu node không phải node lá -> tiếp tục kiểm tra các node con
    if (!node->IsLeaf())
    {
        Retrieve(node->lt, camRect, result);
        Retrieve(node->rt, camRect, result);
        Retrieve(node->lb, camRect, result);
        Retrieve(node->rb, camRect, result);
    }
}

vector<LPGAMEOBJECT> QuadTree::GetObjectsInView(RECT cam)
{
    // Trả về danh sách các object trong vùng nhìn thấy (camera)
    vector<LPGAMEOBJECT> result;
    Retrieve(root, cam, result);
    return result;
}


vector<LPGAMEOBJECT> QuadTree::GetObjectsInView(RECT cam)
{
    vector<LPGAMEOBJECT> result;
    Retrieve(root, cam, result);
    return result;
}
void QuadTree::PrintNode(QNode* node, int level)
{
    if (!node) return;

    // Tạo khoảng trắng theo cấp độ node
    string indent(level * 2, ' ');

    // In thông tin node
    DebugOut(L"%sNode: (%d,%d)-(%d,%d), %d objects\n",
        ToLPCWSTR(indent),
        node->x0, node->y0, node->x1, node->y1,
        (int)node->objects.size());

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

