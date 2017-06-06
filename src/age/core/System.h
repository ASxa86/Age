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
		///	\brief The System in Entity Component System. Override to process game logic for specific components on entities.
		///
		///	\date May 6, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT System : public Object
		{
		public:
			System();
			virtual ~System() override;

			///
			///	Override for frame functionality.
			///
			///	\param x The elapsed/delta time in milliseconds.
			///
			virtual void frame(std::chrono::microseconds x) = 0;
		};
	}
}
