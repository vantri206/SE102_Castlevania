#include "SoundManager.h"
#include <stdexcept>


SoundManager& SoundManager::GetInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::Init() {
    HRESULT hr = XAudio2Create(&xaudio, 0, XAUDIO2_DEFAULT_PROCESSOR);
    if (FAILED(hr)) throw std::runtime_error("Failed to initialize XAudio2");

    hr = xaudio->CreateMasteringVoice(&masterVoice);
    if (FAILED(hr)) throw std::runtime_error("Failed to create mastering voice");
}

void SoundManager::LoadSound(const std::string& id, const std::wstring& filePath) {
    sounds[id] = new Sound(filePath, xaudio, masterVoice);
}

void SoundManager::PlaySound(const std::string& id, bool loop) {
    if (sounds.find(id) != sounds.end()) {
        sounds[id]->Play(loop);
    }
}

void SoundManager::StopSound(const std::string& id) {
    if (sounds.find(id) != sounds.end()) {
        sounds[id]->Stop();
    }
}

void SoundManager::Shutdown() {
    for (auto& pair : sounds) {
        delete pair.second;
    }
    sounds.clear();

    if (masterVoice) masterVoice->DestroyVoice();
    if (xaudio) xaudio->Release();
}

SoundManager::~SoundManager() {
    Shutdown();
}
