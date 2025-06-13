#include "debug.h"
#include "Simon.h"
#include "PhantomBat.h"
#include "Whip.h"
#include "Enemy.h"
#include <cstdlib>
#include "SceneManager.h"
#include "debug.h"
#include <DeadEffect.h>
#define PHANTOMBAT_WIDTH 48
#define PHANTOMBAT_HEIGHT 22
static bool seeded = false;
CPhantomBat::CPhantomBat()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(PHANTOMBAT_ANI_SET_ID));
	this->SetState(PHANTOMBAT_STATE_SLEEPING);
	this->SetAniId(ANI_ID_PHANTOMBAT_SLEEPING);
	this->SetSize(PHANTOMBAT_WIDTH, PHANTOMBAT_HEIGHT);
	attackTarget = D3DXVECTOR2(0.0f, 0.0f);
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = true;
    }
	currentTarget = D3DXVECTOR2(624,168);

	D3DXVECTOR2 backPoint1(528, 128);
	D3DXVECTOR2 backPoint2(784, 128);
	D3DXVECTOR2 backPoint3(784, 64); 
	backPoints.push_back(backPoint1);
	backPoints.push_back(backPoint2);
	backPoints.push_back(backPoint3);

    BatPointGroup group1;
    group1.left = D3DXVECTOR2(536, 128);
    group1.middle = D3DXVECTOR2(620, 96);
    group1.right = D3DXVECTOR2(704, 128);

    BatPointGroup group2;
    group2.left = D3DXVECTOR2(568, 64);
    group2.middle = D3DXVECTOR2(624, 40);
    group2.right = D3DXVECTOR2(680, 64);

    pointGroups.push_back(group1);
    pointGroups.push_back(group2);

    this->health = MAX_HEALTH;
    this->attack = NORMAL_ENEMY_ATTACK;
}

void CPhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt);
    if (this->isDead()) return;
    if (this->health <= 0)
    {
        this->SetState(PHANTOMBAT_STATE_DEAD);
        this->BossEnemyDead(ENEMY_DEAD_TIME);
        EnemyKillByPlayer();
    }
    else if (this->isDead())
    {
        if (GetTickCount64() - startDeathTime >= ENEMY_DEAD_TIME)
            isDeleted = true;
    }
    CSimon* simon = CSceneManager::GetInstance()->GetPlayer();
	DebugOut(L"[PHANTOMBAT] Update: x = %f, y = %f, state = %d\n", x, y, state);
    switch (state)
    {
    case PHANTOMBAT_STATE_SLEEPING:
        if (isActived())
        {
            
            SetState(PHANTOMBAT_STATE_FLYING);
        }
        break;
    case PHANTOMBAT_STATE_HOVERING:
    {
        if (ReachedTarget()) {
            if (SimonInAttackZone())
            {
                SetState(PHANTOMBAT_STATE_ATTACK);
            }
            else if (GetTickCount64() - hovering_start > 1000) // hover 1 giây
            {
                hovering_start = GetTickCount64();
                currentGroupIndex = rand() % pointGroups.size();
                BatPointGroup& group = pointGroups[currentGroupIndex];
                int pick = rand() % 3;
                if (pick == 0) currentTarget = group.left;
                else if (pick == 1) currentTarget = group.middle;
                else currentTarget = group.right;
                FlyTo(currentTarget);
                SetState(PHANTOMBAT_STATE_FLYING);
            }
        }
        break;
    }
    case PHANTOMBAT_STATE_FLYING:
		if (GetTickCount64() - releaseFireballTime >= 1000)
            CreateFireball();
        
        if (ReachedTarget()) {
            if (!issleeping) {
                issleeping = true;
                currentGroupIndex = rand() % pointGroups.size();
                BatPointGroup& group = pointGroups[currentGroupIndex];
                int pick = rand() % 3;
                if (pick == 0) currentTarget = group.left;
                else if (pick == 1) currentTarget = group.middle;
                else currentTarget = group.right;
                FlyTo(currentTarget);
            }
            else if (ReachedTarget(pointGroups[currentGroupIndex].middle)) {
                currentTarget = GetRandomNonMiddlePoint();
                FlyTo(currentTarget);
            }
            else {
                SetState(PHANTOMBAT_STATE_PATROL);
            }
            DebugOut(L"currentGroupIndex = %d", currentGroupIndex);
        }
        
        break;

    case PHANTOMBAT_STATE_PATROL:
        if (patrolcount >= 3) {
            SetState(PHANTOMBAT_STATE_HOVERING);
        }
        else if (ReachedTarget()) {
            BatPointGroup& group = pointGroups[currentGroupIndex];
            if (ReachedTarget(group.middle)) {
                if (directionpoint == 1) {
                   
					currentTarget = group.right;
					FlyTo(currentTarget);
                }
                else {
					currentTarget = group.left;
					FlyTo(currentTarget);
                }
                patrolcount++;
            }
            if (ReachedTarget(group.left)) {
				currentTarget = group.middle;
				FlyTo(currentTarget);
				directionpoint = 1; // Set direction to right
                patrolcount++;
			}
			else if (ReachedTarget(group.right)) {
				currentTarget = group.middle;
				FlyTo(currentTarget);
				directionpoint = -1; // Set direction to left
                patrolcount++;
            }
        }
        break;

    case PHANTOMBAT_STATE_ATTACK:
        if (ReachedTarget()) {
            if (attackTarget.x == 0.0f && attackTarget.y == 0.0f) {
                attackTarget = D3DXVECTOR2(simon->GetX(), simon->GetY());
            }
            if (!isattacked) {
                FlyTo(attackTarget);
            }
            if (ReachedTarget(attackTarget)) {
                isattacked = true;
                currentbackPointIndex = FindNearestPointIndex(attackTarget, backPoints);
                FlyTo(backPoints[currentbackPointIndex]);
            }
            else if (ReachedTarget(backPoints[currentbackPointIndex])) {

                NearestInPointGroupsInfo nearestInfo = FindNearestPointInfoInGroups(backPoints[currentbackPointIndex]);
                currentGroupIndex = nearestInfo.groupIndex;
                currentTarget = nearestInfo.point;
                FlyTo(currentTarget);
                SetState(PHANTOMBAT_STATE_HOVERING);
            }
        }
        break;
    }
    x += vx * dt;
    y += vy * dt;
}

void CPhantomBat::SetState(int newState)
{
    CSimon* simon = CSceneManager::GetInstance()->GetPlayer();
    switch (newState)
    {
    case PHANTOMBAT_STATE_SLEEPING:
		this->SetAniId(ANI_ID_PHANTOMBAT_SLEEPING);
        break;
	case PHANTOMBAT_STATE_HOVERING:
		hovering_start = GetTickCount64(); // Reset hover timer
        this->SetAniId(ANI_ID_PHANTOMBAT_FLYING);
		break;
    case PHANTOMBAT_STATE_FLYING:
        releaseFireballTime = GetTickCount64();
        this->SetAniId(ANI_ID_PHANTOMBAT_FLYING);
        break;

    case PHANTOMBAT_STATE_PATROL:
    {
        this->SetAniId(ANI_ID_PHANTOMBAT_FLYING);
    }
    break;

    case PHANTOMBAT_STATE_ATTACK:
    {
         this->SetAniId(ANI_ID_PHANTOMBAT_FLYING);
         isattacked = false;
		 SetAttackTarget(D3DXVECTOR2(0.0f, 0.0f));
    }
    break;
    }
    this->state = newState;
}


void CPhantomBat::Render()
{
	if (!this->isDead())
		animation_set->at(this->GetAniId())->Render(x, y, nx, width, height);
}

void CPhantomBat::OnNoCollision(DWORD dt) {}

void CPhantomBat::OnCollisionWith(LPCOLLISIONEVENT e) {}

void CPhantomBat::LoadExtraSetting(vector<int> extra_settings) {}

int CPhantomBat::isDead()
{
	return state == PHANTOMBAT_STATE_DEAD;
}
void CPhantomBat::FlyTo(D3DXVECTOR2 target)
{
	DebugOut(L"[PHANTOMBAT] FlyTo: target = (%f, %f)\n", target.x, target.y);
    if (isFlying && !ReachedTarget()) {
        return; 
    }
    currentTarget = target;
    float dx = target.x - x;
    float dy = target.y - y;
    float length = sqrt(dx * dx + dy * dy);
    vx = (dx / length) * flySpeed;
    vy = (dy / length) * flySpeed;
	isFlying = true;
}

bool CPhantomBat::ReachedTarget()
{
    float threshold = 5.0f; // Giảm threshold để chính xác hơn
    bool reached = abs(x - currentTarget.x) < threshold && abs(y - currentTarget.y) < threshold;

    if (reached && isFlying) {
        // Dừng chuyển động khi đến target
        vx = 0;
        vy = 0;
        isFlying = false;
    }

    return reached;
}
bool CPhantomBat::ReachedTarget(D3DXVECTOR2 target)
{
    float threshold = 5.0f; // Giảm threshold để chính xác hơn
    bool reached = abs(x - target.x) < threshold && abs(y - target.y) < threshold;

    if (reached && isFlying) {
        // Dừng chuyển động khi đến target
        vx = 0;
        vy = 0;
        isFlying = false;
    }

    return reached;
}

D3DXVECTOR2 CPhantomBat::GetRandomNonMiddlePoint()
{
    int groupIndex = rand() % pointGroups.size();
    BatPointGroup& group = pointGroups[groupIndex];
    return (rand() % 2 == 0) ? group.left : group.right;
}


D3DXVECTOR2 CPhantomBat::GetAboveMiddlePoint()
{
    BatPointGroup& group = pointGroups[currentGroupIndex];
    return D3DXVECTOR2(group.middle.x, group.middle.y - 32);
}

D3DXVECTOR2 CPhantomBat::GetNearestAboveNonMiddlePoint()
{
    BatPointGroup& group = pointGroups[currentGroupIndex];
    float distLeft = abs(x - group.left.x);
    float distRight = abs(x - group.right.x);
    D3DXVECTOR2 nearest = (distLeft < distRight) ? group.left : group.right;
    return D3DXVECTOR2(nearest.x, nearest.y - 32);
}

void CPhantomBat::TriggerBossDieEffect()
{
}

bool CPhantomBat::SimonInAttackZone()
{
    CSimon* simon = CSceneManager::GetInstance()->GetPlayer();
    return abs(simon->GetX() - x) < 50.0f && abs(simon->GetY() - y) < 50.0f;
}
NearestInPointGroupsInfo CPhantomBat::FindNearestPointInfoInGroups(D3DXVECTOR2 from)
{
    float minDistSq = FLT_MAX;
    NearestInPointGroupsInfo result;

    for (int i = 0; i < pointGroups.size(); ++i)
    {
        BatPointGroup& group = pointGroups[i];
        std::vector<std::pair<D3DXVECTOR2, std::string>> points = {
            {group.left, "left"},
            {group.middle, "middle"},
            {group.right, "right"}
        };
        for (const auto& pair : points)
        {
            const D3DXVECTOR2& pt = pair.first;
            const std::string& type = pair.second;

            float dx = from.x - pt.x;
            float dy = from.y - pt.y;
            float distSq = dx * dx + dy * dy;

            if (distSq < minDistSq)
            {
                minDistSq = distSq;
                result = { pt, i, type };
            }
        }

    }

    return result;
}

int CPhantomBat::FindNearestPointIndex(const D3DXVECTOR2& from, const std::vector<D3DXVECTOR2>& points)
{
    if (points.empty()) return -1; // Trả về -1 nếu danh sách rỗng

    int nearestIndex = 0;
    float minDistSq = (from.x - points[0].x) * (from.x - points[0].x) +
        (from.y - points[0].y) * (from.y - points[0].y);

    for (size_t i = 1; i < points.size(); ++i)
    {
        float dx = from.x - points[i].x;
        float dy = from.y - points[i].y;
        float distSq = dx * dx + dy * dy;

        if (distSq < minDistSq)
        {
            minDistSq = distSq;
            nearestIndex = static_cast<int>(i);
        }
    }

    return nearestIndex;
}
void CPhantomBat::CreateFireball() {
	releaseFireballTime = GetTickCount64();
	CSimon* simon = CSceneManager::GetInstance()->GetPlayer();
	float simonX, simonY;
	simon->GetPosition(simonX, simonY);
	CFireball* fireball = new CFireball(x, y, simonX, simonY);
    CPlayScene* currentPlayScene = CGame::GetInstance()->GetCurrentPlayScene();
    currentPlayScene->AddObject(fireball);
	DebugOut(L"[PHANTOMBAT] CreateFireball at (%f, %f)\n", x, y);
}

void CPhantomBat::BossEnemyDead(int duration)
{
    this->startDeathTime = GetTickCount64();
    this->SetPhysical(0.0f, 0.0f, 0.0f, 0.0f);
    this->TriggerBossDieEffect(duration);
    this->isActive = 0;
}

void CPhantomBat::TriggerBossDieEffect(int duration)
{
    DebugOut(L"%d\n", duration);
    CPlayScene* currentPlayScene = CGame::GetInstance()->GetCurrentPlayScene();
    if (currentPlayScene)
    {
        vector<CDeadEffect*> effects;
        CDeadEffect* deadEffect1 = new CDeadEffect(this->x - 6, this->y, duration);
        CDeadEffect* deadEffect2 = new CDeadEffect(this->x, this->y, duration);
        CDeadEffect* deadEffect3 = new CDeadEffect(this->x + 6, this->y, duration);
        effects.push_back(deadEffect1);
        effects.push_back(deadEffect2);
        effects.push_back(deadEffect3);
        for (auto effect : effects)
        {
            currentPlayScene->AddEffect(effect);
        }
    }
}
void CPhantomBat::ActiveEnemy() {
	isActive = true;
    CSimon* simon = CSceneManager::GetInstance()->GetPlayer();
	simon->StartCombatWithBoss();
}