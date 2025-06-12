#pragma once
#include <Windows.h>
#include <Simon.h>
#include "GameSetting.h"

class CEnemySpawn : public CGameObject
{
protected:

    int enemyType;

    CEnemy* currentEnemy;

    DWORD lastSpawnTime;
    DWORD respawnTime;

    int isActive;

public:

    CEnemySpawn();
    
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

    int IsCanSpawn();
    void CurrentEnemyDead();

    CEnemy* SpawnEnemy();

    void Render(){}

    void SetType(int enemytype);
    int GetEnemyType() const { return enemyType; }

    int IsBlocking() { return 0; }
};
