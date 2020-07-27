#pragma once

#include <azule/math/Vector.h>
#include <azule/physics/CollisionComponent.h>

namespace azule
{
	namespace physics
	{
		///
		///	\struct EdgeCollisionComponent
		///
		///	\brief Define an edge used to determine collision with other collision components.
		///
		///	\author Aaron Shelley
		///
		///	\date February 26, 2019
		///
		struct EdgeCollisionComponent final : public CollisionComponent
		{
			azule::math::Vector Vertex1;
			azule::math::Vector Vertex2;
		};
	}
}
