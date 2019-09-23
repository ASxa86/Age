#pragma once

#ifdef WIN32
#ifdef Age_EnTT_Export
#define AGE_ENTT_EXPORT __declspec(dllexport)
#define AGE_ENTT_EXPORT_C extern "C" __declspec(dllexport)
#else
#define AGE_ENTT_EXPORT __declspec(dllimport)
#define AGE_ENTT_EXPORT_C extern "C" __declspec(dllimport)
#endif
#else
#define AGE_ENTT_EXPORT
#define AGE_ENTT_EXPORT_C extern "C"
#endif
