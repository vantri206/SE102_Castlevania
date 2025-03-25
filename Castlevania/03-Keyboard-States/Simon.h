#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Whip.h"
#include "debug.h"

#define SIMON_WALKING_SPEED		0.1f

#define SIMON_STATE_IDLE	0
#define SIMON_STATE_WALK	1
#define SIMON_STATE_JUMP	2
#define SIMON_STATE_SIT		3
#define SIMON_STATE_ATTACK	4
#define SIMON_STATE_GO_UP	5
#define SIMON_STATE_GO_DOWN 6

#define ID_ANI_SIMON_IDLE		0
#define ID_ANI_SIMON_WALK		1
#define ID_ANI_SIMON_JUMP		2
#define ID_ANI_SIMON_SIT		3
#define ID_ANI_SIMON_ATTACK		4
#define ID_ANI_SIMON_UP_IDLE	5
#define ID_ANI_SIMON_DOWN_IDLE	6
#define ID_ANI_SIMON_GO_UP		7
#define ID_ANI_SIMON_GO_DOWN	8

#define SIMON_WIDTH 15
#define SIMON_HEIGHT 30

class CSimon : public CGameObject
{
protected:
    float maxVx;
    float ax, ay;
    float startx, starty;
    bool isSitting;
    int ani_id;
    CWhip* whip;  // Thêm cây roi

public:
    CSimon(float x, float y) : CGameObject(x, y)
    {
        startx = x; starty = y;
        ax = 0.0f;
        ay = 0.0f;
        nx = 1;
        ny = 1;
        isSitting = false;
        ani_id = 0;
        whip = new CWhip(this);  // Khởi tạo cây roi
    }

    ~CSimon() {
        delete whip;  // Giải phóng bộ nhớ
    }

    void SetDirectionX(int direction) { nx = direction; }
    int GetDirectionX() { return nx; }
    void SetDirectionY(int direction) { ny = direction; }
    int GetDirectionY() { return ny; }
    void Update(DWORD dt) override;
    void Render() override;
    void SetState(int state) override;
    int GetState() { return state; }
    int GetVx() { return vx; }
    CWhip* GetWhip() { return whip; }  // Getter cho whip

    void SimonIdle();
    void SimonWalk();
    void SimonAttack();
    void SimonSit();
    void SimonWalkUp();
};