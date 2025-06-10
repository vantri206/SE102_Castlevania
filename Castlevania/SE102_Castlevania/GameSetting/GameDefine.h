#pragma once

#define WINDOW_CLASS_NAME L"MainWindow"
#define MAIN_WINDOW_TITLE L"Castlevania-NES"
#define WINDOW_ICON_PATH L"castlevania.ico"

#define BACKGROUND_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)
#define BACKGROUND_SPRITES_COLOR D3DCOLOR_XRGB(0, 0, 0)

#define SCREEN_WIDTH 360
#define SCREEN_HEIGHT 270

/*----Direction----*/

#define POSITIVE_DIRECTION -1
#define NEGATIVE_DIRECTION 1

/*-----STAIR DIRECTION----*/

#define UP_STAIR_DIRECTION 1
#define DOWN_STAIR_DIRECTION -1

/*-----Gravity----*/
#define DEFAULT_GRAVITY -0.002f

/*----Define for whip position---*/
#define STANDING 0
#define SITTING 1

/*---Simon weapon----*/
#define PRIMARY_WEAPON 0
#define SUB_WEAPON 1

enum SUBWEAPON_TYPE
{
	DAGGER_TYPE = 0,
	AXE_TYPE = 1,
	HOLYWATERBOTTLE_TYPE = 2,
	STOPWATCH_TYPE = 3
};
/*---- OBJECT_TYPE_ID ----*/

enum OBJECT_TYPE
{
	SIMON = 0,
	WHIP = 1,
	BRICK = 2,
	TORCH = 3,
	BIGHEART = 4,
	PORTAL = 5,
	CANDLE = 6,
	GHOUL = 7,
	PANTHER = 8,
	MONEYBAG = 9,
	STAIR = 10,
	MORNINGSTAR = 11,
	DAGGER = 12,
	AXE = 13,
	HOLYWATERBOTTLE = 14,
	SUBWEAPONITEM = 15,
	SMALLHEART = 16,
	TRIGGERZONE = 17,
	BREAKABLEBRICK = 18,
	WALL = 19,
	BAT = 20,
	WATERDEATHZONE = 21,
};

/*---- Animation Set ----*/

enum ANIMATION_SET_ID
{
	SIMON_ANI_SET_ID = 0,
	WHIP_ANI_SET_ID = 100,
	DAGGER_ANI_SET_ID = 101,
	AXE_ANI_SET_ID = 102,
	HOLYWATER_ANI_SET_ID = 103,
	GHOUL_ANI_SET_ID = 200,
	PANTHER_ANI_SET_ID = 201,
	BAT_ANI_SET_ID = 202,
	TORCH_ANI_SET_ID = 300,
	CANDLE_ANI_SET_ID = 301,
	BREAKABLEBRICK_ANI_SET_ID = 302,
	BIGHEART_ANI_SET_ID = 400,
	SMALLHEART_ANI_SET_ID = 401,
	MONEYBAG_ANI_SET_ID = 410,
	MORNINGSTAR_ANI_SET_ID = 420,
	SUBWEAPONITEM_ANI_SET_ID = 430,
	DEADEFFECT_ANI_SET_ID = 900,
	BREAKBRICKEFFECT_ANI_SET_ID = 901
};

/*----Scene---*/

#define MAX_SCENES 100

#define INTRO_SCENE 0
#define MENU_SCENE 1
#define PLAY_SCENE 2
#define CUT_SCENE 3

/*---- Resource file path ----*/
#define TEXTURES_PATH L"./resource/textures.txt"
#define ANIMATIONS_PATH L"./resource/animations.txt"
#define SPRITES_PATH L"./resource/sprites.txt"
#define ANIMATIONS_SET_PATH L"./resource/animations_set.txt"

#define STAGE1_FILE_PATH L"./resource/Map/Stage1.txt"
#define STAGE1_OBJECT_FILE_PATH L"./resource/Map/Stage1Objects.txt"
#define STAGE2_FILE_PATH L"./resource/Map/Stage2.txt"
#define STAGE2_OBJECT_FILE_PATH L"./resource/Map/Stage2Objects.txt"
#define STAGE3_FILE_PATH L"./resource/Map/Stage3.txt"
#define STAGE3_OBJECT_FILE_PATH L"./resource/Map/Stage3Objects.txt"
#define STAGE4_FILE_PATH L"./resource/Map/Stage4.txt"
#define STAGE5_OBJECT_FILE_PATH L"./resource/Map/Stage4Objects.txt"
#define STAGE5_FILE_PATH L"./resource/Map/Stage5.txt"
#define STAGE5_OBJECT_FILE_PATH L"./resource/Map/Stage5Objects.txt"

#define ALL_SCENES_PATH L"./resource/scenes.txt"

#define MAX_TXT_LINE 1024

#define SIMON_STAIR_DOWN_HEIGHT 32
#define SIMON_IDLE_HEIGHT 32
#define SIMON_SIT_HEIGHT 24