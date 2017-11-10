#pragma once

#include <age/entity/FixedSystem.h>
#include <age/physics/Export.h>

class b2World;

namespace age
{
	namespace physics
	{
		///
		///	\class PhysicsSystem
		///
		///	\brief This system runs on a fixed time step to provide deterministic physics.
		///
		///	\date June 11, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_PHYSICS_EXPORT PhysicsSystem : public age::entity::FixedSystem
		{
		public:
			PhysicsSystem();
			~PhysicsSystem() override;

			///
			/// Provide access the the global physics engine in order to contruct body objects within components.
			///
			static b2World& Engine();

			///
			///	Updates entity transformations using physics.
			///
			void frame(const std::vector<age::entity::Entity>&, std::chrono::microseconds x) override;
		};
	}
}
