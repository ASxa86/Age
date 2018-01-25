#pragma once

#include <age/entity/System.h>
#include <age/physics/Export.h>

namespace age
{
	namespace physics
	{
		class AGE_PHYSICS_EXPORT CollisionSystem : public age::entity::System
		{
		public:
			CollisionSystem();
			~CollisionSystem() override;

			void frame(std::chrono::microseconds x);
		};
	}
}
