#pragma once

#ifdef WIN32
#ifdef AgeNavigation_Export
#define AGE_NAVIGATION_EXPORT __declspec(dllexport)
#else
#define AGE_NAVIGATION_EXPORT __declspec(dllimport)
#endif
#else
#define AGE_NAVIGATION_EXPORT
#endif
