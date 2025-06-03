#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
#include "Whip.h"
#include "Audio/SoundManager.h"


CSimonAttack::CSimonAttack(CSimon* simon)
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
    SoundManager& soundMgr = SoundManager::GetInstance();
    soundMgr.Init();

    soundMgr.LoadSound("use_wp", L"resource/Sounds/SoundEffects/Using_Weapon.wav");
	soundMgr.PlaySound("use_wp");

    CWeapon* currentWeapon;
    simon->GetCurrentWeapon(currentWeapon);
    if (currentWeapon != nullptr) currentWeapon->Render();
}