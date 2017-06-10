#pragma once

#include <age/core/System.h>

namespace age
{
	namespace core
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
		class AGE_CORE_EXPORT VariableSystem : public System
		{
		public:
			VariableSystem();
			~VariableSystem() override;
		};
	}
}
