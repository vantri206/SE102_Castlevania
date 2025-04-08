#pragma once



#define SIMON_START_X 0
#define SIMON_START_Y 0

#define MAX_TXT_LINE 1024

#define WINDOW_CLASS_NAME L"MainWindow"
#define MAIN_WINDOW_TITLE L"Castlevania-NES"
#define WINDOW_ICON_PATH L"castlevania.ico"

#define RESOURCE_FILE_PATH L"resource.txt"


#define BACKGROUND_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)

#define SCREEN_WIDTH 360
#define SCREEN_HEIGHT 270

//Object type 

#define OBJECT_TYPE_SIMON 0
#define OBJECT_TYPE_ENEMIES 1
#define OBJECT_TYPE_WEAPON 2
#define OBJECT_TYPE_ITEM 3
#define OBJECT_TYPE_BRICK 4
#define OBJECT_TYPE_OTHERS 5

// Texture 

#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_WHIP 20

// Animation Sets 

#define SIMON_ANI_SET_ID 0
#define WHIP_ANI_SET_ID 1
#define TORCH_ANI_SET_ID 2

// Id objects

#define SIMON_OBJECTS 0
#define WHIP_OBJECTS 1
#define TORCH_OBJECTS 2
#define BRICK_OBJECTS 3


// Scene define
#define SCENE1 1
#define SCENE2 2

// Map resource

#define STAGE1_FILE_PATH L"./resource/Map/Stage1.txt"
#define STAGE1_OBJECT_FILE_PATH L"./resource/Map/Stage1Objects.txt"