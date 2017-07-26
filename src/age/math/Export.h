#pragma once

#ifdef WIN32
	#ifdef AgeMath_Export
		#define AGE_MATH_EXPORT __declspec(dllexport)
	#else
		#define AGE_MATH_EXPORT __declspec(dllimport)
	#endif
#else
	#define AGE_MATH_EXPORT
#endif
