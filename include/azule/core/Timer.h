#pragma once

#include <azule/export.h>
#include <azule/utilities/Pimpl.h>
#include <chrono>

namespace azule
{
	namespace core
	{
		///
		///	Define a seconds duration using double precision for chrono duration casting.
		///
		typedef std::chrono::duration<double> seconds;

		///
		///	\class Timer
		///
		///	\brief This class manages tracking time.
		///
		///	\date May 16, 2017
		///
		///	\author Aaron Shelley
		///
		class AZULE_EXPORT Timer
		{
		public:
			Timer();
			~Timer();

			///
			///	Resets the timer and returns the time since reset() was last called.
			///
			std::chrono::microseconds reset();

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
