#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
#include "Axe.h"
#include "Whip.h"
#include "HolyWaterBottle.h"
#include "Dagger.h"

#define SIMON_ATTACK_WIDTH 30
#define SIMON_ATTACK_HEIGHT 32

CSimonAttack::CSimonAttack(CSimon* simon, int weaponType) : CSimonState(simon)
{
    simon->SetAniId(ID_ANI_SIMON_ATTACK);
    simon->SetSize(SIMON_ATTACK_WIDTH, SIMON_ATTACK_HEIGHT);
    attackStartTime = GetTickCount64();

    if (weaponType == SUB_WEAPON)
    {
        CWeapon* subWeapon = nullptr;
        float x, y;
        simon->GetPosition(x, y);
        switch (simon->GetCurrentSubType())
        {
        case DAGGER:
            subWeapon = new CDagger(x, y, simon->GetDirectionX());
            break;
        case AXE:
            subWeapon = new CAxe(x, y, simon->GetDirectionX());
            break;
        case HOLYWATERBOTTLE:
            subWeapon = new CHolyWaterBottle(x, y, simon->GetDirectionX());
            break;
        }
        if (subWeapon)
        {
            simon->AddSubWeapon(subWeapon);
            simon->spendHeart(subWeapon->GetHeartCost());
        }
    }
    else
    {
        float x, y;
        simon->GetPosition(x, y);
        CWhip* whip = new CWhip(simon);
        whip->SetPosition(x, y);
        simon->SetCurrentWeapon(whip);
    }
}

CSimonAttack::~CSimonAttack()
{

}

void CSimonAttack::KeyDownHandle(int keyCode) {}
void CSimonAttack::KeyUpHandle(int keyCode) {}

void CSimonAttack::Update(DWORD dt)
{

    if (GetTickCount64() - attackStartTime > SIMON_ATTACK_TIME)
    {
        CWeapon* currentWeapon = nullptr;
        currentWeapon = simon->GetCurrentWeapon();
        if (currentWeapon)
        {
            currentWeapon->Delete();
            delete currentWeapon;
            currentWeapon = nullptr;
            simon->SetCurrentWeapon(nullptr);
        }

        simon->SetState(new CSimonIdle(simon));
        return;
    }
}

void CSimonAttack::OnNoCollision(DWORD dt)
{
	simon->UpdateMoving(dt);
}

void CSimonAttack::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
    {
        CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
        simon->OnCollisionWithEnemy(enemy);
    }
}

void CSimonAttack::Render()
{
    CWeapon* currentWeapon = simon->GetCurrentWeapon();
    if (currentWeapon) currentWeapon->Render();
}