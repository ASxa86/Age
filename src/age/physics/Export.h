#pragma once

#ifdef WIN32
	#ifdef AgePhysics_Export
		#define AGE_PHYSICS_EXPORT __declspec(dllexport)
	#else
		#define AGE_PHYSICS_EXPORT __declspec(dllimport)
	#endif
#else
	#define AGE_PHYSICS_EXPORT
#endif
