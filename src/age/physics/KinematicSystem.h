#pragma once

#include <age/core/FixedSystem.h>
#include <age/physics/Export.h>

class b2World;

namespace age
{
	namespace physics
	{
		///
		///	\class KinematicSystem
		///
		///	\brief This system runs on a fixed time step to provide deterministic physics.
		///
		///	\date June 11, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_PHYSICS_EXPORT KinematicSystem : public age::core::FixedSystem
		{
		public:
			KinematicSystem();
			~KinematicSystem() override;

			///
			///	Updates entity transformations using physics.
			///
			void frame(std::chrono::microseconds x) override;

			b2World& getPhysicsEngine();

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
