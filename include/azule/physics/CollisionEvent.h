#pragma once

#include <azule/core/Event.h>
#include <azule/utilities/Pimpl.h>
#include <azule/physics/export.h>
#include <vector>

namespace azule
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
		class AZULE_PHYSICS_EXPORT CollisionEvent : public azule::core::Event
		{
		public:
			///
			///	\param x The entity that collided.
			///
			CollisionEvent(const azule::entity::Entity& a, const azule::entity::Entity& b);
			~CollisionEvent() override;

			const azule::entity::Entity& getEntityA();
			const azule::entity::Entity& getEntityB();

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
