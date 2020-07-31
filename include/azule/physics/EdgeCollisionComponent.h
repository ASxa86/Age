#pragma once

#include <azule/math/Vector.h>
#include <azule/physics/CollisionComponent.h>

namespace azule
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
		azule::Vector Vertex1;
		azule::Vector Vertex2;
	};
}
