#pragma once

#ifdef WIN32
	#ifdef AgeGraphics_Export
		#define AGE_GRAPHICS_EXPORT __declspec(dllexport)
	#else
		#define AGE_GRAPHICS_EXPORT __declspec(dllimport)
	#endif
#else
	#define AGE_GRAPHICS_EXPORT
#endif
