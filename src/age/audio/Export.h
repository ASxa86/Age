#pragma once

#ifdef WIN32
#ifdef AgeAudio_Export
#define AGE_AUDIO_EXPORT __declspec(dllexport)
#else
#define AGE_AUDIO_EXPORT __declspec(dllimport)
#endif
#else
#define AGE_AUDIO_EXPORT
#endif
