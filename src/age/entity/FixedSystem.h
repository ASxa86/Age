#pragma once

#include <age/entity/System.h>

namespace age
{
	namespace entity
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
		class AGE_ENTITY_EXPORT FixedSystem : public System
		{
		public:
			FixedSystem();
			virtual ~FixedSystem() override = 0;
		};
	}
}
