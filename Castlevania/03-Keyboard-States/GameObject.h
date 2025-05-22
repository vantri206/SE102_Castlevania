#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include "Animation.h"
#include "Animations.h"
#include "Collision.h"
using namespace std;

class CGameObject
{
protected:

    int type;
    int id;

    float x, y;
    float vx, vy;
    float width, height;

    int nx, ny;

    int state;
    int ani_id;

	bool isDeleted;

    CAnimationSet animations;
    LPANIMATION_SET animation_set;

public:

    void SetType(int type) { this->type = type; }
    void SetId(int id) { this->id = id; }
    int GetType() { return type; }
    int GetId() { return id; }

    float GetX() { return x; }
    float GetY() { return y; }
    void SetPosition(float x, float y) { this->x = x; this->y = y; }
    void GetPosition(float& x, float& y) { x = this->x; y = this->y; }

    float GetDirection(int& nx, int& ny) { nx = this->nx;ny = this->ny; }
    void SetDirectionX(int nx) { this->nx = nx; }
    void SetDirectionY(int ny) { this->ny = ny; }

    float GetWidth() { return width; }
    float GetHeight() { return height; }
    void SetSize(float width, float height) { this->width = width; this->height = height; }
    void GetSize(float& width, float& height) { width = this->width; height = this->height; }

    void SetVx(float vx) { this->vx = vx; }
    void SetVy(float vy) { this->vy = vy; }
    void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

    void SetAniId(int ani_id) { this->ani_id = ani_id; }
    int GetAniId() { return this->ani_id; }

    virtual int GetState() { return state; }
    virtual void SetState(int state) { this->state = state; }

    void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
    virtual void Render() = 0;
    void RenderBoundingBox();

    virtual int IsCollidable() { return 0; };
    virtual int CanCollisionWithObj(LPGAMEOBJECT objDests) { return 1; };

    virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

    virtual int IsBlocking() { return 1; }

    virtual int IsOverlappable() { return 0; }

	virtual int IsDirectionColliable(int nx, int ny) { return 1; }

    void GetBoundingBox(float& l, float& t, float& r, float& b);

    virtual void Delete() { isDeleted = true; }
    virtual bool IsDeleted() { return this->isDeleted; }
    static bool IsDeleted(const LPGAMEOBJECT& obj) { return obj->isDeleted; }

    virtual void LoadExtraSetting(vector<int> extra_settings) {}

    CGameObject();
    virtual ~CGameObject();

};

typedef CGameObject* LPGAMEOBJECT;
