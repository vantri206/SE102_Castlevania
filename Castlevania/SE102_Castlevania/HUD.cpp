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
        if(i < playerHP)
            sprites->Get(SPRITES_PLAYERHP_ID)->Draw(healthStartX + i * 6 + HUD_HP_WIDTH / 2, healthY + HUD_HP_HEIGHT / 2, 1, HUD_HP_WIDTH, HUD_HP_HEIGHT);
        else
            sprites->Get(SPRITES_LOSTHP_ID)->Draw(healthStartX + i * 6 + HUD_HP_WIDTH / 2, healthY + HUD_HP_HEIGHT / 2, 1, HUD_HP_WIDTH, HUD_HP_HEIGHT);


    healthY -= 10;
    for (int i = 0; i < 16; i++)
        if (i < enemyHP)
            sprites->Get(SPIRTES_ENEMYHP_ID)->Draw(healthStartX + i * 6 + HUD_HP_WIDTH / 2, healthY + HUD_HP_HEIGHT / 2, 1, HUD_HP_WIDTH, HUD_HP_HEIGHT);
        else
            sprites->Get(SPRITES_LOSTHP_ID)->Draw(healthStartX + i * 6 + HUD_HP_WIDTH / 2, healthY + HUD_HP_HEIGHT / 2, 1, HUD_HP_WIDTH, HUD_HP_HEIGHT);

    float pointX = 75;
    float pointY = -4;
    RECT rect;
    SetRect(&rect, pointX, pointY, pointX + 64, pointY + 13);

    std::wstringstream text;
    text << std::setw(6) << std::setfill(L'0') << score;
    font->DrawText(spriteHandler, text.str().c_str(), -1, &rect, DT_LEFT, D3DXCOLOR(1, 1, 1, 1));

    float timeX = 164;
    float timeY = -4;

    SetRect(&rect, timeX, timeY, timeX + 64, timeY + 13);

    text.str(L"");
    text << std::setw(3) << std::setfill(L'0') << time;
    font->DrawText(spriteHandler, text.str().c_str(), -1, &rect, DT_LEFT, D3DXCOLOR(1, 1, 1, 1));

    float stageX = 252;
    float stageY = -4;

    SetRect(&rect, stageX, stageY, stageX + 64, stageY + 13);

    text.str(L"");
    text << std::setw(2) << std::setfill(L'0') << stage;
    font->DrawText(spriteHandler, text.str().c_str(), -1, &rect, DT_LEFT, D3DXCOLOR(1, 1, 1, 1));

    float heartX = 218;
    float heartY = 6.5;

    SetRect(&rect, heartX, heartY, heartX + 64, heartY + 13);

    text.str(L"");
    text << std::setw(2) << std::setfill(L'0') << hearts;
    font->DrawText(spriteHandler, text.str().c_str(), -1, &rect, DT_LEFT, D3DXCOLOR(1, 1, 1, 1));

    float lifeX = 218;
    float lifeY = 17;

    SetRect(&rect, lifeX, lifeY, lifeX + 64, lifeY + 13);

    text.str(L"");
    text << std::setw(2) << std::setfill(L'0') << life;
    font->DrawText(spriteHandler, text.str().c_str(), -1, &rect, DT_LEFT, D3DXCOLOR(1, 1, 1, 1));

    int subweaponSpritesId;
    float spriteWidth, spriteHeight;
    switch (subweapontype)
    {
    case DAGGER:
        subweaponSpritesId = DAGGER_SPRITES_ID;
        spriteWidth = 16;
        spriteHeight = 10;
        break;
    case AXE:
        subweaponSpritesId = AXE_SPRITES_ID;
        spriteWidth = 15;
        spriteHeight = 14;
        break;
    case HOLYWATERBOTTLE:
        subweaponSpritesId = HOLYWATER_BOTTLE_SPRITES_ID;
        spriteWidth = 16;
        spriteHeight = 16;
        break;
    default:
        subweaponSpritesId = 0;
        spriteWidth = 0;
        spriteHeight = 0;
    }
    CSprites::GetInstance()->Get(subweaponSpritesId)->Draw(statusbarX + 28, statusbarY - 1, 1, spriteWidth, spriteHeight);
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

void CHUD::SetSubWeapon(int subweapon)
{
    this->subweapontype = subweapon;
}