#pragma once

#include <age/physics/CollisionComponent.h>

namespace age
{
	namespace physics
	{
		struct BoxCollisionComponent final : public CollisionComponent
		{
			double Width;
			double Height;
		};
	}
}
