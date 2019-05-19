#pragma once

#ifdef WIN32
#ifdef AgeGraphics_Export
#define AGE_GRAPHICS_EXPORT __declspec(dllexport)
#define AGE_GRAPHICS_EXPORT_C extern "C" __declspec(dllexport)
#else
#define AGE_GRAPHICS_EXPORT __declspec(dllimport)
#define AGE_GRAPHICS_EXPORT_C extern "C" __declspec(dllimport)
#endif
#else
#define AGE_GRAPHICS_EXPORT
#define AGE_GRAPHICS_EXPORT_C
#endif
