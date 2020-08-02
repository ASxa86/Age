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
		glm::vec2 Vertex1;
		glm::vec2 Vertex2;
	};
}
