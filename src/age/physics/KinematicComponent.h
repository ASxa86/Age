#pragma once

#include <age/core/Object.h>
#include <age/math/Vector.h>
#include <age/physics/Export.h>

namespace age
{
	namespace physics
	{
		///
		///	\class KinematicComponent
		///
		///	\brief A component for managing velocity in a physical world.
		///
		///	\date June 11, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_PHYSICS_EXPORT KinematicComponent : public age::core::Object
		{
		public:
			KinematicComponent();
			~KinematicComponent() override;

			///
			///	Set the velocity vector.
			///	(m/s)
			///
			void setVelocity(const age::math::Vector& x);

			///
			///	Get the velocity vector.
			///	(m/s)
			///
			age::math::Vector getVelocity() const;

			///
			///	Set the angular velocity.
			///	(deg/s)
			///
			void setAngularVelocity(double x);

			///
			///	Get the angular velocity.
			///	(deg/s)
			///
			double getAngularVelocity() const;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
