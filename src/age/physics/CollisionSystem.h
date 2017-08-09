#pragma once

#include <age/core/FixedSystem.h>
#include <age/physics/Export.h>

namespace age
{
	namespace physics
	{
		class AGE_PHYSICS_EXPORT CollisionSystem : public age::core::FixedSystem
		{
		public:
			CollisionSystem();
			~CollisionSystem() override;

			void frame(std::chrono::microseconds x) override;
		};
	}
}