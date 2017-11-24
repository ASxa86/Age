#pragma once

#include <age/entity/FixedSystem.h>
#include <age/physics/Export.h>

namespace age
{
	namespace physics
	{
		class AGE_PHYSICS_EXPORT CollisionSystem : public age::entity::FixedSystem
		{
		public:
			CollisionSystem();
			~CollisionSystem() override;

			void frame(std::chrono::microseconds x) override;
		};
	}
}