#pragma once

#ifdef WIN32
#ifdef AgeMathQt_Export
#define AGE_MATH_QT_EXPORT __declspec(dllexport)
#define AGE_MATH_QT_EXPORT_C extern "C" __declspec(dllexport)
#else
#define AGE_MATH_QT_EXPORT __declspec(dllimport)
#define AGE_MATH_QT_EXPORT_C extern "C" __declspec(dllimport)
#endif
#else
#define AGE_MATH_QT_EXPORT
#endif
