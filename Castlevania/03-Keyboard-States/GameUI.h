#pragma once
#include "GameObject.h"
#include <string>
#include <d3d10.h>

#define UI_PADDING 10
#define UI_BUTTON_WIDTH 100
#define UI_BUTTON_HEIGHT 30
#define UI_VOLUME_BAR_WIDTH 150
#define UI_VOLUME_BAR_HEIGHT 10
#define UI_BACKGROUND_COLOR D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f)  // Semi-transparent gray
#define UI_BUTTON_COLOR D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f)      // Light gray
#define UI_SELECTED_COLOR D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)    // White for selected item
#define UI_TEXT_COLOR D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)        // White

enum class MenuOption {
    PAUSE,
    SAVE,
    LOAD,
    VOLUME,
    TOTAL_OPTIONS
};

class GameUI : public CGameObject {
private:
    bool isPaused;
    bool isVisible;
    float volume;
    MenuOption selectedOption;
    RECT pauseButton;
    RECT saveButton;
    RECT loadButton;
    RECT volumeBar;
    RECT volumeSlider;

public:
    GameUI();
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    virtual void Render();
    
    void DrawButton(ID3D10Device* d3ddev, RECT rect, LPCSTR text, D3DXCOLOR color);
    void DrawRect(ID3D10Device* d3ddev, RECT rect, D3DXCOLOR color);
    void HandleKeyboard();
    void SelectNextOption();
    void SelectPreviousOption();
    void ExecuteSelectedOption();
    void AdjustVolume(bool increase);
    bool IsVisible() { return isVisible; }
    void ToggleVisible() { isVisible = !isVisible; }
    bool IsPaused() { return isPaused; }
    void TogglePause() { isPaused = !isPaused; }
    void SetVolume(float newVolume) { volume = max(0.0f, min(1.0f, newVolume)); }
    float GetVolume() { return volume; }
    void SaveGame();
    void LoadGame();

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};