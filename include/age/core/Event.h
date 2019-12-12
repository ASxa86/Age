#pragma once

#include <age/core/export.h>

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

			Event(const Event&) = delete;
			Event& operator=(const Event&) = delete;
		};
	}
}
