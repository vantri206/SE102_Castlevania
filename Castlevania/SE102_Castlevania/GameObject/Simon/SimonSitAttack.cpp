#include "Simon.h"
#include "SimonSitAttack.h"
#include "SimonSit.h"
#include "Axe.h"
#include "Whip.h"
#include "HolyWaterBottle.h"
#include "Dagger.h"

#define SIMON_SIT_ATTACK_WIDTH 30
#define SIMON_SIT_ATTACK_HEIGHT 24

CSimonSitAttack::CSimonSitAttack(CSimon* simon, int weaponType) : CSimonState(simon)
{
    simon->SetAniId(ID_ANI_SIMON_SIT_ATTACK);
    simon->SetSize(SIMON_SIT_ATTACK_WIDTH, SIMON_SIT_ATTACK_HEIGHT);
    attackStartTime = GetTickCount64();

    if (weaponType == SUB_WEAPON)
    {
        CWeapon* subWeapon = nullptr;
        float x, y;
        simon->GetPosition(x, y);
        x += simon->GetWidth() / 2;
        y += simon->GetHeight() / 3;
        switch (simon->GetCurrentSubType())
        {
        case DAGGER_TYPE:
            subWeapon = new CDagger(x, y, simon->GetDirectionX());
            break;
        case AXE_TYPE:
            subWeapon = new CAxe(x, y, simon->GetDirectionX());
            break;
        case HOLYWATERBOTTLE_TYPE:
            subWeapon = new CHolyWaterBottle(x, y, simon->GetDirectionX());
            break;
        }
        simon->AddSubWeapon(subWeapon);
        simon->spendHeart(subWeapon->GetHeartCost());
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

CSimonSitAttack::~CSimonSitAttack()
{

}

void CSimonSitAttack::KeyDownHandle(int keyCode) {}
void CSimonSitAttack::KeyUpHandle(int keyCode) {}

void CSimonSitAttack::Update(DWORD dt)
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
        simon->SetState(new CSimonSit(simon));
        return;
    }
}

void CSimonSitAttack::OnNoCollision(DWORD dt)
{
}

void CSimonSitAttack::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
    {
        CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
        simon->OnCollisionWithEnemy(enemy);
    }
}

void CSimonSitAttack::Render()
{
    CWeapon* currentWeapon = simon->GetCurrentWeapon();
    if (currentWeapon) currentWeapon->Render();
}