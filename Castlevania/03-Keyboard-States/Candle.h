#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "GameDefine.h"
#define CANDLE_STATE_BURN 0
#define CANDLE_ANI_BURN 0
#define CANDLE_WIDTH 8
#define CANDLE_HEIGHT 16
class CCandle : public CGameObject
{
protected:
    int object_drop_id;
    bool appearing = false;
    float appearStartY = 0;
    float targetY = 0;
    float appearSpeed = 0.0025f; // Tốc độ hiện lên
public:
    CCandle();
    CCandle(float x, float y);
    void StartAppearing();
    void Render();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void LoadExtraSetting(vector<int> extra_settings);
    void SetTargetY(float y) { targetY = y; }
    int IsBlocking() { return 0; }
    int IsColliable() { return 1; }
};