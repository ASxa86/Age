#pragma once

#ifdef WIN32
#ifdef AgeEntity_Export
#define AGE_ENTITY_EXPORT __declspec(dllexport)
#define AGE_ENTITY_EXPORT_C extern "C" __declspec(dllexport)
#else
#define AGE_ENTITY_EXPORT __declspec(dllimport)
#define AGE_ENTITY_EXPORT_C extern "C" __declspec(dllimport)
#endif
#else
#define AGE_ENTITY_EXPORT
#define AGE_ENTITY_EXPORT_C
#endif
