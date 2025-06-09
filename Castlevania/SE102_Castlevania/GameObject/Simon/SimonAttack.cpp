#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
#include "Whip.h"

#define SIMON_ATTACK_WIDTH 30
#define SIMON_ATTACK_HEIGHT 32

CSimonAttack::CSimonAttack(CSimon* simon, int weaponType) : CSimonState(simon)
{
    attackStartTime = GetTickCount64();
    simon->SetAniId(ID_ANI_SIMON_ATTACK);

    if (weaponType == SUB_WEAPON)
    {
        CWeapon* subWeapon = nullptr;
        float x, y; 
        simon->GetPosition(x, y);
        x += simon->GetWidth() / 2;
        y += simon->GetHeight() / 3;
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

void CSimonAttack::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonAttack::KeyUpHandle(CSimon* simon, int keyCode) {}

void CSimonAttack::Update(CSimon* simon, DWORD dt)
{

    if (GetTickCount64() - attackStartTime > SIMON_ATTACK_TIME)
    {
        CWeapon* currentWeapon = nullptr;
        simon->GetCurrentWeapon(currentWeapon);
        currentWeapon->Delete();
        delete currentWeapon;
        simon->SetCurrentWeapon(nullptr);

        simon->SetState(new CSimonIdle(simon));
        return;
    }
}

void CSimonAttack::OnNoCollision(CSimon* simon, DWORD dt)
{
}

void CSimonAttack::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CEnemy*>(e->obj))
    {
        CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
        simon->OnCollisionWithEnemy(enemy);
    }
}

void CSimonAttack::Render(CSimon* simon)
{
    CWeapon* currentWeapon;
    simon->GetCurrentWeapon(currentWeapon);
    if (currentWeapon != nullptr) currentWeapon->Render();
}