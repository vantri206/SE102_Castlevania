#pragma once

#include <d3d10.h>
#include <d3dx10.h>

#define DAGGER_SPRITES_ID 50030
#define AXE_SPRITES_ID 50031
#define HOLYWATER_BOTTLE_SPRITES_ID 50032


class CHUD
{
private:

	static CHUD* _instance;

	ID3DX10Font* font;
	ID3D10Device* d3dDevice;

	int playerHP;
	int enemyHP;
	int maxHP;
	int score;
	int time;
	int stage;
	int hearts;
	int life;
	int subweapontype;
	int displayedScore;

public:
	static CHUD* GetInstance(ID3D10Device* device = nullptr);
	CHUD(ID3D10Device* device);
	~CHUD();
	void Render();

	//HUD info

	void SetPlayerHP(int hp);
	void SetEnemyHP(int hp);
	int GetScore();
	void SetScore(int s);
	void SetTime(int t);
	void SetStage(int s);
	void SetHeart(int h);
	void SetLife(int l);
	void SetSubWeapon(int subweapon);
};
