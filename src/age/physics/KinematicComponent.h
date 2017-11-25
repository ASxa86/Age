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
			///	Set the position within the world.
			///	(m)
			///
			void setPosition(const age::math::Vector& x);

			///
			///	Get the position within the world.
			///	(m)
			///
			age::math::Vector getPosition() const;

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
			///	Set the rotation.
			///	(deg)
			///
			void setRotation(double x);

			///
			///	Get the rotation.
			///	(deg)
			///
			double getRotation() const;

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
			age::math::Vector position;
			age::math::Vector velocity;
			double rotation;
			double angularVelocity;
		};
	}
}
