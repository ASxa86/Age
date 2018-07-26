#pragma once

#include <age/physics/Export.h>

class b2Body;

namespace age
{
	namespace entity
	{
		class Entity;
	}

	namespace physics
	{
		class PhysicsSystem;

		///
		///	\class BodyComponent
		///
		///	\brief A wrapper around a Box2D b2Body in order to handle destruct of a b2Body when this component is removed.
		///
		///	\author Aaron Shelley
		///
		///	\date July 25, 2018
		///
		class AGE_PHYSICS_EXPORT BodyComponent
		{
		public:
			BodyComponent(PhysicsSystem& x, const age::entity::Entity& e);
			~BodyComponent();
			b2Body* body;
		};
	}
}
