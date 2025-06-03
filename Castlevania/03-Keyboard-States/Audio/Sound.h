#pragma once
#include <xaudio2.h>
#include <string>
#include "WavLoader.h"

class Sound {
public:
    Sound(const std::wstring& filePath, IXAudio2* xaudio, IXAudio2MasteringVoice* masterVoice);
    ~Sound();
    void Play(bool loop = false);
    void Stop();

private:
    IXAudio2SourceVoice* sourceVoice = nullptr;
    XAUDIO2_BUFFER buffer = {};
    BYTE* audioData = nullptr;
    WAVEFORMATEX waveFormat = {};
};
