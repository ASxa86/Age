#pragma once

#include <age/entity/System.h>
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
		class AGE_PHYSICS_EXPORT PhysicsSystem : public age::entity::System
		{
		public:
			PhysicsSystem();
			~PhysicsSystem() override;

			///
			///	Updates entity transformations using physics.
			///
			void frame(std::chrono::microseconds x);

			///
			///	Get the internal Box2D world that is used to drive this physics system.
			///
			b2World& getWorld();

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
