#pragma once

#ifdef WIN32
#ifdef Age_TMX_Export
#define AGE_TMX_EXPORT __declspec(dllexport)
#define AGE_TMX_EXPORT_C extern "C" __declspec(dllexport)
#else
#define AGE_TMX_EXPORT __declspec(dllimport)
#define AGE_TMX_EXPORT_C extern "C" __declspec(dllimport)
#endif
#else
#define AGE_TMX_EXPORT
#define AGE_TMX_EXPORT_C extern "C"
#endif
