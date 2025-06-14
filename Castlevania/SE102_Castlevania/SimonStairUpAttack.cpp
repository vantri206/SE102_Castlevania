#include "Simon.h"
#include "SimonStairUpAttack.h"
#include "SimonIdle.h"
#include "Axe.h"
#include "Whip.h"
#include "HolyWaterBottle.h"
#include "Dagger.h"
#include "SimonStairUpIdle.h"

#define SIMON_STAIR_UP_ATTACK_WIDTH 30
#define SIMON_STAIR_UP_ATTACK_HEIGHT 32

CSimonStairUpAttack::CSimonStairUpAttack(CSimon* simon) : CSimonState(simon)
{
    simon->SetAniId(ID_ANI_SIMON_ATTACK_UP);
    simon->SetSize(SIMON_STAIR_UP_ATTACK_WIDTH, SIMON_STAIR_UP_ATTACK_HEIGHT);
    attackStartTime = GetTickCount64();
        float x, y;
        simon->GetPosition(x, y);
        CWhip* whip = new CWhip(simon);
        whip->SetPosition(x, y);
        simon->SetCurrentWeapon(whip);
}

CSimonStairUpAttack::~CSimonStairUpAttack()
{

}

void CSimonStairUpAttack::KeyDownHandle(int keyCode) {}
void CSimonStairUpAttack::KeyUpHandle(int keyCode) {}

void CSimonStairUpAttack::Update(DWORD dt)
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
        simon->SetState(new CSimonStairUpIdle(simon));
        return;
    }
}

void CSimonStairUpAttack::OnNoCollision(DWORD dt)
{
}

void CSimonStairUpAttack::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
    {
        CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
        simon->OnCollisionWithEnemy(enemy);
    }
}

void CSimonStairUpAttack::Render()
{
    CWeapon* currentWeapon = simon->GetCurrentWeapon();
    if (currentWeapon) currentWeapon->Render();
}