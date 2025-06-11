#include "GameUI.h"
#include "Game.h"
#include "debug.h"

GameUI::GameUI() {
    isPaused = false;
    isVisible = false;  // Menu ẩn khi khởi tạo
    volume = 1.0f;
    selectedOption = MenuOption::PAUSE;

    // Initialize button positions
    int screenWidth = CGame::GetInstance()->GetBackBufferWidth();
    int screenHeight = CGame::GetInstance()->GetBackBufferHeight();

    // Setup button positions at the top of the screen
    pauseButton = { UI_PADDING, UI_PADDING, UI_PADDING + UI_BUTTON_WIDTH, UI_PADDING + UI_BUTTON_HEIGHT };
    saveButton = { UI_PADDING * 2 + UI_BUTTON_WIDTH, UI_PADDING, UI_PADDING * 2 + UI_BUTTON_WIDTH * 2, UI_PADDING + UI_BUTTON_HEIGHT };
    loadButton = { UI_PADDING * 3 + UI_BUTTON_WIDTH * 2, UI_PADDING, UI_PADDING * 3 + UI_BUTTON_WIDTH * 3, UI_PADDING + UI_BUTTON_HEIGHT };
    
    // Volume bar on the right side
    volumeBar = { 
        screenWidth - UI_PADDING - UI_VOLUME_BAR_WIDTH,
        UI_PADDING,
        screenWidth - UI_PADDING,
        UI_PADDING + UI_VOLUME_BAR_HEIGHT
    };
    volumeSlider = volumeBar;
    volumeSlider.right = volumeBar.left + (int)((volumeBar.right - volumeBar.left) * volume);
}

void GameUI::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    // Xử lý phím ESC để bật/tắt menu
    static bool escPressed = false;
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        if (!escPressed) {
            ToggleVisible();
            if (isVisible) {
                isPaused = true;  // Tự động pause game khi mở menu
            } else {
                isPaused = false; // Tự động unpause khi đóng menu
            }
            escPressed = true;
        }
    } else {
        escPressed = false;
    }

    // Chỉ xử lý input khi menu đang hiển thị
    if (isVisible) {
        HandleKeyboard();
    }
}

void GameUI::HandleKeyboard() {
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        if (selectedOption == MenuOption::VOLUME) {
            AdjustVolume(false);
        } else {
            SelectPreviousOption();
        }
    }
    
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        if (selectedOption == MenuOption::VOLUME) {
            AdjustVolume(true);
        } else {
            SelectNextOption();
        }
    }
    
    if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
        ExecuteSelectedOption();
    }
}

void GameUI::SelectNextOption() {
    int next = static_cast<int>(selectedOption) + 1;
    if (next >= static_cast<int>(MenuOption::TOTAL_OPTIONS))
        next = 0;
    selectedOption = static_cast<MenuOption>(next);
}

void GameUI::SelectPreviousOption() {
    int prev = static_cast<int>(selectedOption) - 1;
    if (prev < 0)
        prev = static_cast<int>(MenuOption::TOTAL_OPTIONS) - 1;
    selectedOption = static_cast<MenuOption>(prev);
}

void GameUI::ExecuteSelectedOption() {
    switch (selectedOption) {
        case MenuOption::PAUSE:
            TogglePause();
            break;
        case MenuOption::SAVE:
            SaveGame();
            break;
        case MenuOption::LOAD:
            LoadGame();
            break;
        case MenuOption::VOLUME:
            // Volume is adjusted using left/right arrows
            break;
    }
}

void GameUI::AdjustVolume(bool increase) {
    float volumeChange = 0.1f;
    if (!increase) volumeChange = -volumeChange;
    SetVolume(volume + volumeChange);
    volumeSlider.right = volumeBar.left + (int)((volumeBar.right - volumeBar.left) * volume);
}

void GameUI::DrawRect(ID3D10Device* d3ddev, RECT rect, D3DXCOLOR color) {
    CGame::GetInstance()->DrawFillRect(rect, color);
}

void GameUI::DrawButton(ID3D10Device* d3ddev, RECT rect, LPCSTR text, D3DXCOLOR color) {
    DrawRect(d3ddev, rect, color);
    // TODO: Add text rendering if needed
}

void GameUI::Render() {
    // Chỉ render khi menu đang visible
    if (!isVisible) return;

    // Draw buttons with alpha blending
    D3DXCOLOR buttonColor = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.9f);  // Light gray with alpha
    D3DXCOLOR selectedColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // White
    D3DXCOLOR bgColor = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);      // Dark gray with alpha

    DrawButton(nullptr, pauseButton, isPaused ? "Resume" : "Pause", 
               selectedOption == MenuOption::PAUSE ? selectedColor : buttonColor);
    DrawButton(nullptr, saveButton, "Save", 
               selectedOption == MenuOption::SAVE ? selectedColor : buttonColor);
    DrawButton(nullptr, loadButton, "Load", 
               selectedOption == MenuOption::LOAD ? selectedColor : buttonColor);
    
    // Draw volume control background
    DrawRect(nullptr, volumeBar, 
             selectedOption == MenuOption::VOLUME ? selectedColor : bgColor);
    
    // Draw volume level
    DrawRect(nullptr, volumeSlider, buttonColor);
}

void GameUI::SaveGame() {
    DebugOut(L"[INFO] Saving game...\n");
}

void GameUI::LoadGame() {
    DebugOut(L"[INFO] Loading game...\n");
}