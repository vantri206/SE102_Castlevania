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

    float x;
    float y;
    float width;
    float height;
    float vx;
    float vy;

    int nx;
    int ny;

    int state;
    int ani_id;

	bool isDeleted;

    CAnimationSet animations;
    LPANIMATION_SET animation_set;

public:
    float GetX() { return x; }
    float GetY() { return y; }
    float GetWidth() { return width; }
    float GetHeight() { return height; }
    void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSize(float width, float height) { this->width = width; this->height = height; }
    void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSize(float& width, float& height) { width = this->width; height = this->height; }
    void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	void SetVy(float vy) { this->vy = vy; }
    void SetAniId(int ani_id) { this->ani_id = ani_id; }
    int GetAniId() { return this->ani_id; }

    int GetState() { return state; }
    void SetState(int state) { this->state = state; }

    CGameObject();

    void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
    virtual void Render() = 0;

    virtual int IsCollidable() { return 0; };

    virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	virtual int IsBlocking() { return 0; };

	virtual int IsDirectionColliable(int nx, int ny) { return 1; }

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
    virtual ~CGameObject();
    static bool IsDeleted(const LPGAMEOBJECT& o) { return o->isDeleted; }

    virtual void LoadExtraSetting(vector<int> extra_settings) {}

	void SetType(int type) { this->type = type; }
	void SetId(int id) { this->id = id; }

};

typedef CGameObject* LPGAMEOBJECT;
