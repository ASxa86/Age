#pragma once

#ifdef WIN32
	#ifdef AgeCore_Export
		#define AGE_CORE_EXPORT __declspec(dllexport)
	#else
		#define AGE_CORE_EXPORT __declspec(dllimport)
	#endif
#else
	#define AGE_CORE_EXPORT
#endif
