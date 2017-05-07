#pragma once

#include <age/core/Export.h>
#include <cstdint>

namespace age
{
	namespace core
	{
		///
		///	\class Event
		///
		///	\brief This class manages the different event types that are available.
		///
		///	\date April 28, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT Event
		{
		public:
			Event();
			virtual ~Event();
		};
	}
}
