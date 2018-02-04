#pragma once

#include <age/core/Event.h>
#include <age/core/Pimpl.h>
#include <age/physics/Export.h>
#include <vector>

namespace age
{
	namespace entity
	{
		class Entity;
	}

	namespace physics
	{
		///
		///	\class Collision Event
		///
		///	\brief This event contains relevant information pertaining to a single collision between entities.
		///
		///	\date February 3, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_PHYSICS_EXPORT CollisionEvent : public age::core::Event
		{
		public:
			///
			///	\param x The entity that collided.
			///
			CollisionEvent();
			~CollisionEvent() override;

			///
			///	Add an entity that has made contact with another entity.
			///
			void addEntity(age::entity::Entity e);

			///
			///	Get a list of entities that have made contact with other entities.
			///
			const std::vector<age::entity::Entity>& getEntities() const;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
