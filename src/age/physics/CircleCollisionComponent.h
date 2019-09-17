#pragma once

#include <age/physics/CollisionComponent.h>

namespace age
{
	namespace physics
	{
		///
		///	\struct CircleCollisionComponent
		///
		///	\brief Define the size of a circle used to determine collision with other collision components.
		///
		///	\author Aaron Shelley
		///
		///	\date February 26, 2019
		///
		struct AGE_PHYSICS_EXPORT CircleCollisionComponent final : public CollisionComponent
		{
			CircleCollisionComponent();

			double Radius;
		};
	}
}
