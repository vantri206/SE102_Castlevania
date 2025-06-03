#include "WavLoader.h"
#include <mmreg.h>
#include <mmiscapi.h>
#include <mmsystem.h>
#include <cassert>

#pragma comment(lib, "winmm.lib")

bool LoadWavFile(const wchar_t* filename, BYTE** audioData, WAVEFORMATEX* waveFormat, XAUDIO2_BUFFER* buffer) {
    HMMIO file = mmioOpenW((LPWSTR)filename, NULL, MMIO_READ | MMIO_ALLOCBUF);
    if (!file) return false;

    MMCKINFO riffChunk = {};
    riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    if (mmioDescend(file, &riffChunk, NULL, MMIO_FINDRIFF)) return false;

    MMCKINFO fmtChunk = {};
    fmtChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(file, &fmtChunk, &riffChunk, MMIO_FINDCHUNK)) return false;

    DWORD fmtSize = fmtChunk.cksize;
    BYTE* fmtData = new BYTE[fmtSize];
    mmioRead(file, (HPSTR)fmtData, fmtSize);
    *waveFormat = *(WAVEFORMATEX*)fmtData;
    delete[] fmtData;
    mmioAscend(file, &fmtChunk, 0);

    MMCKINFO dataChunk = {};
    dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(file, &dataChunk, &riffChunk, MMIO_FINDCHUNK)) return false;

    DWORD dataSize = dataChunk.cksize;
    *audioData = new BYTE[dataSize];
    mmioRead(file, (HPSTR)(*audioData), dataSize);

    buffer->AudioBytes = dataSize;
    buffer->pAudioData = *audioData;
    buffer->Flags = XAUDIO2_END_OF_STREAM;

    mmioClose(file, 0);
    return true;
}
