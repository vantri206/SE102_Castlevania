#include "EnemySpawn.h"
#include "Ghoul.h"
#include "FishMan.h"
#include "Bat.h"
#include "Panther.h"
#include <Camera.h>

CEnemySpawn::CEnemySpawn()
{
    this->enemyType = -1;
    this->respawnTime = 0;
    this->lastSpawnTime = -1;
    this->isActive = false;
    this->currentEnemy = nullptr;
}

void CEnemySpawn::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (isActive && currentEnemy && currentEnemy->isDead())
    {
        CurrentEnemyDead();
    }

    if (isActive) return;   //has current enemy, cant spawn

    DWORD now = GetTickCount64();
    if (now - lastSpawnTime < respawnTime)  return;

    if (IsCanSpawn())
    {
        CPlayScene* currentPlayScene = CGame::GetInstance()->GetCurrentPlayScene();
        CSimon* player = CSceneManager::GetInstance()->GetPlayer();
        currentEnemy = SpawnEnemy();
        if (currentEnemy)
        {
            currentEnemy->SetPosition(x, y);
            currentEnemy->SetDirectionX(player->GetX() < x ? -1 : 1);
            currentPlayScene->AddObject(currentEnemy);
            isActive = true;
        }
    }
}

int CEnemySpawn::IsCanSpawn()
{
    CSimon* player = CSceneManager::GetInstance()->GetPlayer();
    float playerX, playerY;
    player->GetPosition(playerX, playerY);

    switch (enemyType)
    {
    case FISHMAN:
        return (abs(playerX - this->x) <= FISHMAN_ACTIVE_RANGEX && abs(playerY - this->y) <= FISHMAN_ACTIVE_RANGEY);
        break;
    case BAT:
    case GHOUL:
    case PANTHER:
    {
        return (!CCamera::GetInstance()->IsInCamera(this));
        break;
    }
    default: 
        return 0;
    }
}

CEnemy* CEnemySpawn::SpawnEnemy()
{
    CEnemy* enemy = nullptr;
    switch (enemyType)
    {
    case GHOUL:
        enemy = new CGhoul();
        break;
    case PANTHER:
        enemy = new CPanther();
        break;
    case BAT:
        enemy = new CBat();
        break;
    case FISHMAN:
        enemy = new CFishMan();
        break;
    default: break;
    }
    return enemy;
}

void CEnemySpawn::SetType(int enemytype)
{
    this->enemyType = enemytype;
    switch (enemytype)
    {
    case GHOUL:
        respawnTime = GHOUL_SPAWN_TIME;
        break;
    case FISHMAN:
        respawnTime = FISHMAN_SPAWN_TIME;
        break;
    case BAT:
        respawnTime = BAT_SPAWN_TIME;
        break;
    default: 
        respawnTime = 0;
    }
}

void CEnemySpawn::CurrentEnemyDead()
{
    isActive = false;
    lastSpawnTime = GetTickCount64();
    currentEnemy = nullptr;
}