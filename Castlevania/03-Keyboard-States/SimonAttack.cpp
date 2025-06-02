#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
#include "Whip.h"
#include "Dagger.h"

CSimonAttack::CSimonAttack(CSimon* simon, int weaponType) : CSimonState(simon)
{
    simon->SetAniId(ID_ANI_SIMON_ATTACK);
    attackStartTime = GetTickCount64();

    if (weaponType == SUB_WEAPON)
    {
        CWeapon* subWeapon = nullptr;
        float x, y;
        simon->GetPosition(x, y);
        switch (simon->GetCurrentSubType())
        {
        case DAGGER_TYPE:
            subWeapon = new CDagger(simon->GetX(), simon->GetY(), simon->GetDirectionX());
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

CSimonAttack::~CSimonAttack()
{

}

void CSimonAttack::KeyDownHandle(int keyCode) {}
void CSimonAttack::KeyUpHandle(int keyCode) {}

void CSimonAttack::Update(DWORD dt)
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
        simon->SetState(new CSimonIdle(simon));
        return;
    }
}

void CSimonAttack::OnNoCollision(DWORD dt)
{
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