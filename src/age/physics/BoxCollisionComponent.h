#pragma once

#include <age/physics/CollisionComponent.h>

namespace age
{
	namespace physics
	{
		///
		///	\struct BoxCollisionComponent
		///
		///	\brief Define the size of a box used to determine collision with other collision components.
		///
		///	\author Aaron Shelley
		///
		///	\date February 26, 2019
		///
		struct BoxCollisionComponent final : public CollisionComponent
		{
			double Width;
			double Height;
		};
	}
}
