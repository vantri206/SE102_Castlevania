#include "Simon.h"
#include "SimonAttack.h"
#include "SimonIdle.h"
#include "Whip.h"

CSimonAttack::CSimonAttack(CSimon* simon)
{
    attackStartTime = GetTickCount64();
    simon->SetAniId(ID_ANI_SIMON_ATTACK);
    
    // Create whip
    whip = new CWhip();
    whip->SetDirectionX(simon->GetDirectionX());
    
    // Calculate whip position based on Simon's direction
    float whip_x;
    if (simon->GetDirectionX() > 0)
        whip_x = simon->GetX() + SIMON_WIDTH/2 + WHIP_BBOX_WIDTH/2;  // Center of Simon + half width of whip
    else
        whip_x = simon->GetX() - SIMON_WIDTH/2;  // Center of Simon - half width of whip
        
    float whip_y = simon->GetY() + WHIP_BBOX_HEIGHT/2; // Same vertical center as Simon
    whip->SetPosition(whip_x, whip_y);
}

CSimonAttack::~CSimonAttack()
{
    if (whip)
    {
        delete whip;
        whip = nullptr;
    }
}

void CSimonAttack::KeyDownHandle(CSimon* simon, int keyCode) {}
void CSimonAttack::KeyUpHandle(CSimon* simon, int keyCode) {}

void CSimonAttack::Update(CSimon* simon, DWORD dt)
{
    if (GetTickCount64() - attackStartTime > 300)
    {
        if (whip)
        {
            whip->SetFinished(true);
        }
        simon->SetState(new CSimonIdle(simon));
        return;
    }

    // Update whip position based on Simon's position and direction
    if (whip)
    {
        float whip_x;
        if (simon->GetDirectionX() > 0)
            whip_x = simon->GetX() + SIMON_WIDTH/2 + WHIP_BBOX_WIDTH/2;  // Center of Simon + half width of whip
        else
            whip_x = simon->GetX() - SIMON_WIDTH/2;  // Center of Simon - half width of whip
            
        float whip_y = simon->GetY() + WHIP_BBOX_HEIGHT / 2;  // Same vertical center as Simon
        whip->SetPosition(whip_x, whip_y);
        whip->Update(dt, simon->GetCoObjects());
    }
}

void CSimonAttack::OnNoCollision(CSimon* simon, DWORD dt)
{
}

void CSimonAttack::OnCollisionWith(CSimon* simon, LPCOLLISIONEVENT e)
{
}

void CSimonAttack::Render(CSimon* simon)
{
    if (whip)
    {
        whip->Render();
    }
}
