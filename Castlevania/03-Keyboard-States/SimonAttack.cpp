#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
#include "Whip.h"

CSimonAttack::CSimonAttack(CSimon* simon) : CSimonState(simon)
{
    attackStartTime = GetTickCount64();
    simon->SetAniId(ID_ANI_SIMON_ATTACK);
    float x, y;
    simon->GetPosition(x, y);
    CWhip* whip = new CWhip(simon);
    whip->SetPosition(x, y);
    simon->SetCurrentWeapon(whip);
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
        simon->GetCurrentWeapon(currentWeapon);
        currentWeapon->Delete();
        delete currentWeapon;
        simon->SetCurrentWeapon(nullptr);
       
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
    CWeapon* currentWeapon;
    simon->GetCurrentWeapon(currentWeapon);
    if (currentWeapon != nullptr) currentWeapon->Render();
}