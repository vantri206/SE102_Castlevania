#pragma once
#include "GameObject.h"

#define ANI_ID_BUTTONSTART_NOTPRESSED 0
#define ANI_ID_BUTTONSTART_PRESSED 1

#define BUTTON_START_WIDTH 112
#define BUTTON_START_HEIGHT 8

class CButtonStart : public CGameObject
{
private:
public:
    CButtonStart(float x, float y);

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr) {}
    void Render();
    void ButtonPressed();
};
