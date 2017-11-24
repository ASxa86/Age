#pragma once

#include <age/entity/System.h>

namespace age
{
	namespace entity
	{
		///
		///	\class VariableSystem
		///
		///	\brief Abstract class for processing a single variable time frame.
		///
		///	\date June 9, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_ENTITY_EXPORT VariableSystem : public System
		{
		public:
			VariableSystem();
			virtual ~VariableSystem() override = 0;
		};
	}
}
