#pragma once

#ifdef WIN32
#ifdef AgeCoreQt_Export
#define AGE_CORE_QT_EXPORT __declspec(dllexport)
#define AGE_CORE_QT_EXPORT_C extern "C" __declspec(dllexport)
#else
#define AGE_CORE_QT_EXPORT __declspec(dllimport)
#define AGE_CORE_QT_EXPORT_C extern "C" __declspec(dllimport)
#endif
#else
#define AGE_CORE_QT_EXPORT
#endif
