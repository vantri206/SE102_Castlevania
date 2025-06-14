#include "Simon.h"
#include "SimonStairDownAttack.h"
#include "SimonIdle.h"
#include "Axe.h"
#include "Whip.h"
#include "HolyWaterBottle.h"
#include "Dagger.h"
#include "SimonStairDownIdle.h"

#define SIMON_STAIR_DOWN_ATTACK_WIDTH 28
#define SIMON_STAIR_DOWN_ATTACK_HEIGHT 32

CSimonStairDownAttack::CSimonStairDownAttack(CSimon* simon) : CSimonState(simon)
{
    simon->SetAniId(ID_ANI_SIMON_ATTACK_DOWN);
    simon->SetSize(SIMON_STAIR_DOWN_ATTACK_WIDTH, SIMON_STAIR_DOWN_ATTACK_HEIGHT);
    attackStartTime = GetTickCount64();
    float x, y;
    simon->GetPosition(x, y);
    CWhip* whip = new CWhip(simon);
    whip->SetPosition(x, y);
    simon->SetCurrentWeapon(whip);
}

CSimonStairDownAttack::~CSimonStairDownAttack()
{

}

void CSimonStairDownAttack::KeyDownHandle(int keyCode) {}
void CSimonStairDownAttack::KeyUpHandle(int keyCode) {}

void CSimonStairDownAttack::Update(DWORD dt)
{

    if (GetTickCount64() - attackStartTime > SIMON_ATTACK_TIME)
    {
        CWeapon* currentWeapon = simon->GetCurrentWeapon();
        if (currentWeapon)
        {
            currentWeapon->Delete();
            delete currentWeapon;
            simon->SetCurrentWeapon(nullptr);
        }
        simon->SetState(new CSimonStairDownIdle(simon));
        return;
    }
}

void CSimonStairDownAttack::OnNoCollision(DWORD dt)
{
}

void CSimonStairDownAttack::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
    {
        CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
        simon->OnCollisionWithEnemy(enemy);
    }
}

void CSimonStairDownAttack::Render()
{
    CWeapon* currentWeapon = simon->GetCurrentWeapon();
    if (currentWeapon) currentWeapon->Render();
}