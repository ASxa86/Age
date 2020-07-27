#pragma once

#include <azule/entity/System.h>
#include <azule/physics/export.h>

namespace azule
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
		class AZULE_PHYSICS_EXPORT PhysicsSystem : public azule::entity::System
		{
		public:
			PhysicsSystem();
			~PhysicsSystem() override;

			void onStartup() override;

			///
			///	Updates entity transformations using physics.
			///
			void frame(std::chrono::microseconds x);

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
