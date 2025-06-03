#pragma once
#include <xaudio2.h>
#include <map>
#include <string>
#include "Sound.h"

class SoundManager {
public:
    static SoundManager& GetInstance();
    void Init();
    void LoadSound(const std::string& id, const std::wstring& filePath);
    void PlaySound(const std::string& id, bool loop = false);
    void StopSound(const std::string& id);
    void Shutdown();

private:
    SoundManager() = default;
    ~SoundManager();
    IXAudio2* xaudio = nullptr;
    IXAudio2MasteringVoice* masterVoice = nullptr;
    std::map<std::string, Sound*> sounds;
};
