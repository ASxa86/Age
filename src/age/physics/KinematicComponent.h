#pragma once

#include <age/physics/Export.h>
#include <age/math/Vector.h>

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
		class AGE_PHYSICS_EXPORT KinematicComponent
		{
		public:
			KinematicComponent();
			~KinematicComponent();

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
			age::math::Vector velocity;
			double angularVelocity;
		};
	}
}
