#pragma once

#include <age/core/Event.h>
#include <age/utilities/Pimpl.h>
#include <age/physics/export.h>
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
			CollisionEvent(const age::entity::Entity& a, const age::entity::Entity& b);
			~CollisionEvent() override;

			const age::entity::Entity& getEntityA();
			const age::entity::Entity& getEntityB();

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
