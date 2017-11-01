#pragma once

#include <age/core/Object.h>
#include <age/entity/EntityManager.h>
#include <chrono>

namespace age
{
	namespace entity
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
		class AGE_ENTITY_EXPORT System : public age::core::Object
		{
		public:
			System();
			virtual ~System() override;

			///
			///	Override for frame functionality.
			///
			///	\param x The elapsed/delta time in milliseconds.
			///
			virtual void frame(const std::vector<Entity>& entities, std::chrono::microseconds x) = 0;

		protected:
			///
			///	Systems perform work on entities. This provides a convenient way to collect them.
			///
			EntityManager* getEntityManager() const;
		};
	}
}
