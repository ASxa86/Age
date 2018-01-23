#pragma once

#include <age/entity/FixedSystem.h>
#include <age/physics/Export.h>

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

			void initialize() override;

			///
			///	Updates entity transformations using physics.
			///
			void frame(std::chrono::microseconds x) override;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
