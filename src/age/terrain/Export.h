#pragma once

#ifdef WIN32
#ifdef AgeTerrain_Export
#define AGE_TERRAIN_EXPORT __declspec(dllexport)
#else
#define AGE_TERRAIN_EXPORT __declspec(dllimport)
#endif
#else
#define AGE_TERRAIN_EXPORT
#endif
