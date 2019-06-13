#pragma once

#include <age/math/Vector.h>
#include <age/physics/CollisionComponent.h>

namespace age
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
			age::math::Vector Vertex1;
			age::math::Vector Vertex2;
		};
	}
}
