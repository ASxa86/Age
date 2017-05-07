#pragma once

#include <age/core/Object.h>
#include <chrono>

namespace age
{
	namespace core
	{
		///
		///	\class Processor
		///
		///	\brief Abstract class for processing a single non-fixed time frame.
		///
		///	\date May 6, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT Processor : public Object
		{
		public:
			Processor();
			virtual ~Processor();

			///
			///	Preframe is called by the engine before frame. This is useful for polling events.
			///
			virtual void preframe();

			///
			///	Override for frame functionality.
			///
			///	\param x The elapsed/delta time in milliseconds.
			///
			virtual void frame(const std::chrono::milliseconds& x) = 0;
		};
	}
}
