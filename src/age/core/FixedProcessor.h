#pragma once

#include <age/core/Processor.h>
#include <chrono>

namespace age
{
	namespace core
	{
		///
		///	\class FixedProcessor
		///
		///	\brief Abstract class for processing a single fixed time frame.
		///
		///	\date May 6, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT FixedProcessor : public Processor
		{
		public:
			FixedProcessor();
			virtual ~FixedProcessor();
		};
	}
}
