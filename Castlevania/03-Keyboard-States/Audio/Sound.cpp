#include "Sound.h"
#include <stdexcept>

Sound::Sound(const std::wstring& filePath, IXAudio2* xaudio, IXAudio2MasteringVoice* masterVoice) {
    if (!LoadWavFile(filePath.c_str(), &audioData, &waveFormat, &buffer)) {
        throw std::runtime_error("Failed to load WAV file");
    }

    HRESULT hr = xaudio->CreateSourceVoice(&sourceVoice, &waveFormat);
    if (FAILED(hr)) {
        throw std::runtime_error("Failed to create source voice");
    }
}

Sound::~Sound() {
    if (sourceVoice) {
        sourceVoice->DestroyVoice();
    }
    delete[] audioData;
}

void Sound::Play(bool loop) {
    sourceVoice->Stop(0);
    sourceVoice->FlushSourceBuffers();
    buffer.LoopCount = loop ? XAUDIO2_LOOP_INFINITE : 0;
    sourceVoice->SubmitSourceBuffer(&buffer);
    sourceVoice->Start(0);
}

void Sound::Stop() {
    sourceVoice->Stop(0);
    sourceVoice->FlushSourceBuffers();
}
