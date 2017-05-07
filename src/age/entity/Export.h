#pragma once

#ifdef WIN32
	#ifdef AgeEntity_Export
		#define AGE_ENTITY_EXPORT __declspec(dllexport)
	#else
		#define AGE_ENTITY_EXPORT __declspec(dllimport)
	#endif
#else
	#define AGE_ENTITY_EXPORT
#endif
