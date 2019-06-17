#pragma once

#ifdef WIN32
#ifdef AgePhysics_Export
#define AGE_PHYSICS_EXPORT __declspec(dllexport)
#define AGE_PHYSICS_EXPORT_C extern "C" __declspec(dllexport)
#else
#define AGE_PHYSICS_EXPORT __declspec(dllimport)
#define AGE_PHYSICS_EXPORT_C extern "C" __declspec(dllimport)
#endif
#else
#define AGE_PHYSICS_EXPORT
#define AGE_PHYSICS_EXPORT_C
#endif
