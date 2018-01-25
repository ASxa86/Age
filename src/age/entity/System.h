#pragma once

#include <age/core/Processor.h>
#include <age/entity/Export.h>
#include <chrono>

namespace age
{
	namespace entity
	{
		class EntityManager;

		///
		///	\class Processor
		///
		///	\brief The System in Entity Component System. Override to process game logic for specific components on entities.
		///
		///	\date May 6, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_ENTITY_EXPORT System : public age::core::Processor
		{
		public:
			System();
			virtual ~System() override;

		protected:
			///
			///	Systems perform work on entities. This provides a convenient way to collect them.
			///
			EntityManager* getEntityManager() const;
		};
	}
}
