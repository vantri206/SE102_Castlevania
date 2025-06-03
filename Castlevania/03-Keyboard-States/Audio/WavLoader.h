#pragma once
#include <windows.h>
#include <xaudio2.h>

bool LoadWavFile(const wchar_t* filename, BYTE** audioData, WAVEFORMATEX* waveFormat, XAUDIO2_BUFFER* buffer);
