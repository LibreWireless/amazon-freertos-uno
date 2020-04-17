/**
Libre Wireless Technologies
 **/


#ifndef _AUDIO_H
#define _AUDIO_H

//Dependencies
#include "os_port.h"
#include "error.h"
#include "avs_defs.h"

//Miscellaneous macros
#define AUDIO_COPY_MONO_BUFFER(dest, src, length) memcpy(dest, src, (length) * sizeof(AudioMonoPcmSample))
#define AUDIO_CLEAR_MONO_BUFFER(dest, length) memset(dest, 0, (length) * sizeof(AudioMonoPcmSample))

#define AUDIO_COPY_STEREO_BUFFER(dest, src, length) memcpy(dest, src, (length) * sizeof(AudioStereoPcmSample))
#define AUDIO_CLEAR_STEREO_BUFFER(dest, length) memset(dest, 0, (length) * sizeof(AudioStereoPcmSample))

/**
 * @brief PCM buffer (mono)
 **/

#include "avs.h"


/**
 * @brief PCM sample (stereo)
 **/
#ifdef HD_SUPPORT
typedef struct
{
    int32_t left;
    int32_t right;
} AudioStereoPcmSample;
#else
typedef struct
{
    int16_t left;
    int16_t right;
} AudioStereoPcmSample;
#endif


/**
 * @brief PCM buffer (stereo)
 **/

typedef struct
{
    AudioMonoPcmSample *data;
    size_t size;
    size_t threshold;
    size_t length;
    size_t writePos;
    size_t readPos;
    bool clearInProgress;
} AudioMonoPcmBuffer;


/**
 * @brief PCM buffer (stereo)
 **/

typedef struct
{
    AudioStereoPcmSample *data;
    size_t size;
    size_t startthreshold;
	size_t writethreshold;
    size_t length;
    size_t writePos;
    size_t readPos;
	bool flush;
    bool clearBufInProgress;
} AudioStereoPcmBuffer;


//Win32 compiler?
#if defined(_WIN32)
#pragma pack(push, 1)
#endif


/**
 * @brief WAV file header
 **/

typedef __start_packed struct
{
    uint8_t riffId[4];
    uint32_t riffChunkSize;
    uint8_t waveId[4];
    uint8_t fmtId[4];
    uint32_t fmtChunckSize;
    uint16_t format;
    uint16_t channels;
    uint32_t samplesPerSec;
    uint32_t bytesPerSec;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    uint8_t dataId[4];
    uint32_t dataChunckSize;
} __end_packed WavHeader;


//Win32 compiler?
#if defined(_WIN32)
#pragma pack(pop)
#endif

//Audio related functions

void AvsAudioInit();

#endif
