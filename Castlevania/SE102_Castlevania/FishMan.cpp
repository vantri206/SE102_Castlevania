#include "FishMan.h"
#include "Simon.h"
#include "GameSetting.h"
#include <Fireball.h>
#include <WaterDeadZone.h>

CFishMan::CFishMan()
{
    this->SetAnimationSet(CAnimationSets::GetInstance()->Get(FISHMAN_ANI_SET_ID));
    this->SetState(FISHMAN_STATE_JUMP);
    this->SetAniId(ANI_ID_FISHMAN_JUMP);
    this->SetSize(FISHMAN_WIDTH, FISHMAN_HEIGHT);
    this->SetPhysical(0.0f, 0.0f, 0.0f, 0.0f);

    this->startAttackTime = -1;
    this->lastAttackTime = -1;

    health = FISHMAN_HP;
}

void CFishMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (!(isDead() || isActived()))
    {
        CSimon* player = CSceneManager::GetInstance()->GetPlayer();
        if (this->CheckEnemyCanActive(player)) ActiveEnemy();
    }
    if (this->isDead())
    {
        if (GetTickCount64() - startDeathTime >= ENEMY_DEAD_TIME)
            isDeleted = true;
        return;
    }

    if (!isActived()) return;

    if (this->health <= 0)
    {
        this->SetState(FISHMAN_STATE_DEAD);
        this->NormalEnemyDead(ENEMY_DEAD_TIME);
    }
    else
    {
        vy += ay * dt;
        CCollision::GetInstance()->Process(this, dt, coObjects);
    }
    DWORD now = GetTickCount64();
    if (state == FISHMAN_STATE_JUMP && vy == 0)
    {
        this->SetState(FISHMAN_STATE_WALK);
        lastAttackTime = now;
    }
    if (state == FISHMAN_STATE_ATTACK)
    {
        if (now - startAttackTime > FISHMAN_ATTACK_TIME)
        {
            this->CreateFireball();
            startAttackTime = -1;
            lastAttackTime = now;
            nx = (-1) * nx;
            this->SetState(FISHMAN_STATE_WALK);
        }
    }
    if (state == FISHMAN_STATE_WALK && now - lastAttackTime > FISHMAN_ATTACK_COOLDOWN)
    {
        startAttackTime = now;
        this->SetState(FISHMAN_STATE_ATTACK);
    }
}

void CFishMan::Render()
{
    if (this->isActived() && !this->isDead())
        animation_set->at(this->GetAniId())->Render(x, y, nx, width, height);
}

void CFishMan::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CFishMan::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj)) return;
    else if (dynamic_cast<CWaterDeadZone*>(e->obj))
    {
        float l, t, r, b;
        e->obj->GetBoundingBox(l, t, r, b);
        this->TriggerSplashEffect(x, t);
    }
    else if (e->ny != 0 && e->obj->IsBlocking())
    {
        vy = 0.0f;
    }
}

int CFishMan::IsCollidable()
{
    return (state != FISHMAN_STATE_DEAD);
}

void CFishMan::SetState(int state)
{
    switch (state)
    {
    case FISHMAN_STATE_JUMP:
    {
        this->ani_id = ANI_ID_FISHMAN_JUMP;
        this->SetPhysical(0.0f, FISHMAN_JUMP_SPEED, 0.0f, FISHMAN_GRAVITY);
        break;
    }
    case FISHMAN_STATE_WALK:
    {
        this->ani_id = ANI_ID_FISHMAN_WALK;
        this->SetPhysical(FISHMAN_RUN_SPEED * nx, 0.0f, 0.0f, FISHMAN_GRAVITY);
        break;
    }
    case FISHMAN_STATE_ATTACK:
    {
        this->ani_id = ANI_ID_FISHMAN_ATTACK;
        this->SetPhysical(0.0f, 0.0f, 0.0f, DEFAULT_GRAVITY);
        break;
    }
    case FISHMAN_STATE_DEAD:
        this->ani_id = ANI_ID_FISHMAN_JUMP;
        this->SetPhysical(0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
    this->state = state;
}

void CFishMan::LoadExtraSetting(vector<int> extra_settings)
{
    if (extra_settings.size() > 0)
        this->SetDirectionX(extra_settings[0]);
}

int CFishMan::CheckEnemyCanActive(CSimon* simon)
{
    float simonX, simonY;
    simon->GetPosition(simonX, simonY);
    float distanceX = abs(simonX - x);
    float distanceY = abs(simonY - y);
    if (distanceX <= FISHMAN_ACTIVE_RANGEX && distanceY <= FISHMAN_ACTIVE_RANGEY)
        return 1;
    return 0;
}

void CFishMan::CreateFireball()
{
    float l, t, r, b;
    this->GetBoundingBox(l, t, r, b);
    CFireball* fireball = new CFireball(x, t - FISHMAN_HEIGHT/4, this->nx);
    CPlayScene* currentPlayScene = CGame::GetInstance()->GetCurrentPlayScene(); 
    currentPlayScene->AddObject(fireball);
}
void CFishMan::ActiveEnemy()
{
    isActive = true;
    this->SetState(FISHMAN_STATE_JUMP);
}

int CFishMan::isDead()
{
    return (state == FISHMAN_STATE_DEAD);
}
