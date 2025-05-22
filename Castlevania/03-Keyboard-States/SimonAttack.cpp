#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
#include "Whip.h"

CSimonAttack::CSimonAttack(CSimon* simon)
{
    attackStartTime = GetTickCount64();
    simon->SetAniId(ID_ANI_SIMON_ATTACK);
    
    float x, y;
    simon->GetPosition(x, y);
    whip = new CWhip();
    whip->SetPosition(x, y);
    whip->SetOwner(simon);
    CScene* scene = CGame::GetInstance()->GetCurrentScene();
    scene->AddObject(whip);
}

CSimonAttack::~CSimonAttack()
{
    if (whip != NULL)
        whip->Delete();
}

void CSimonAttack::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonAttack::KeyUpHandle(CSimon* simon, int keyCode) {}

void CSimonAttack::Update(CSimon* simon, DWORD dt)
{
    whip->Update(dt, simon->GetCoObjects());
    if (GetTickCount64() - attackStartTime > SIMON_ATTACK_TIME)
    {
        simon->SetState(new CSimonIdle(simon));
        return;
    }
}

void CSimonAttack::OnNoCollision(CSimon* simon, DWORD dt)
{
}

void CSimonAttack::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{

}

void CSimonAttack::Render()
{
    if(whip) whip->Render();
}