#pragma once

#include <azule/core/export.h>

namespace azule
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
		class AZULE_CORE_EXPORT Event
		{
		public:
			Event();
			virtual ~Event();

			Event(const Event&) = delete;
			Event& operator=(const Event&) = delete;
		};
	}
}
