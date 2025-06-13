#include "HUD.h"
#include <string>
#include <sstream>
#include <Sprites.h>
#include <Camera.h>
#include <debug.h>
#include <iomanip>

CHUD* CHUD::_instance = nullptr;

CHUD* CHUD::GetInstance(ID3D10Device* device)
{
    if (_instance == nullptr && device != nullptr)
        _instance = new CHUD(device);
    return _instance;
}

CHUD::CHUD(ID3D10Device* device)
{
    this->d3dDevice = device;

    D3DX10_FONT_DESC fontDesc = {
        16,                        
        0,                         
        FW_BOLD,                  
        1,                       
        FALSE,                    
        DEFAULT_CHARSET,          
        OUT_DEFAULT_PRECIS,     
        NONANTIALIASED_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, 
        L"Consolas"              
    };

    D3DX10CreateFontIndirect(device, &fontDesc, &font);

    playerHP = 0;
    enemyHP = 0;
    maxHP = 16;
    score = 0;
    time = 300;
    stage = 1;
    hearts = 5;
    life = 3;
    displayedScore = 0;
}

CHUD::~CHUD()
{
    if (font) font->Release();
}

void CHUD::Render()
{
    DebugOut(L"%f\n", score);
    float cx = (FLOAT)floor(CCamera::GetInstance()->GetX());
    float cy = (FLOAT)floor(CCamera::GetInstance()->GetY());

    CSprites* sprites = CSprites::GetInstance();
    CGame* game = CGame::GetInstance();
    ID3DX10Sprite* spriteHandler = game->GetSpriteHandler();

    float statusbarX = cx + HUD_WIDTH / 1.75;
    float statusbarY = cy + (SCREEN_HEIGHT) - 1.75 * HUD_HEIGHT;

    sprites->Get(SPRITES_STATUSBAR_ID)->Draw(statusbarX, statusbarY, -1, HUD_WIDTH, HUD_HEIGHT);

    float healthStartX = statusbarX - 80;
    float healthY = statusbarY - 2;
    for (int i = 0; i < 16; i++)
        if(i < maxHP)
            sprites->Get(SPRITES_PLAYERHP_ID)->Draw(healthStartX + i * 6 + HUD_HP_WIDTH / 2, healthY + HUD_HP_HEIGHT / 2, 1, HUD_HP_WIDTH, HUD_HP_HEIGHT);
        else
            sprites->Get(SPRITES_LOSTHP_ID)->Draw(healthStartX + i * 6 + HUD_HP_WIDTH / 2, healthY + HUD_HP_HEIGHT / 2, 1, HUD_HP_WIDTH, HUD_HP_HEIGHT);


    healthY -= 10;
    for (int i = 0; i < 16; i++)
        if (i < maxHP)
            sprites->Get(SPIRTES_ENEMYHP_ID)->Draw(healthStartX + i * 6 + HUD_HP_WIDTH / 2, healthY + HUD_HP_HEIGHT / 2, 1, HUD_HP_WIDTH, HUD_HP_HEIGHT);
        else
            sprites->Get(SPRITES_LOSTHP_ID)->Draw(healthStartX + i * 6 + HUD_HP_WIDTH / 2, healthY + HUD_HP_HEIGHT / 2, 1, HUD_HP_WIDTH, HUD_HP_HEIGHT);

    float pointX = 75;
    float pointY = -4;
    RECT rect;
    SetRect(&rect, pointX, pointY, pointX + 64, pointY + 16);

    std::wstringstream text;
    text << std::setw(6) << std::setfill(L'0') << score;
    font->DrawText(spriteHandler, text.str().c_str(), -1, &rect, DT_LEFT, D3DXCOLOR(1, 1, 1, 1));
}

void CHUD::SetPlayerHP(int hp)
{
    playerHP = hp;
    if (playerHP > maxHP) playerHP = maxHP;
    if (playerHP < 0) playerHP = 0;
}

void CHUD::SetEnemyHP(int hp)
{
    enemyHP = hp;
    if (enemyHP > maxHP) enemyHP = maxHP;
    if (enemyHP < 0) enemyHP = 0;
}

int CHUD::GetScore()
{
    return score;
}
void CHUD::SetScore(int s)
{
    score = s;
}

void CHUD::SetTime(int t)
{
    time = t;
}

void CHUD::SetStage(int s)
{
    stage = s;
}

void CHUD::SetHeart(int h)
{
    hearts = h;
}

void CHUD::SetLife(int l)
{
    life = l;
}
