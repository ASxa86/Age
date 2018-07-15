#pragma once

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
		class AGE_PHYSICS_EXPORT KinematicComponent
		{
		public:
			enum class BodyType : uint8_t
			{
				/// No physics simulation is applied.
				Static,

				/// Physics simulation and only collides with dynamic types.
				Kinematic,

				/// All physics simulations and collision.
				Dynamic
			};

			KinematicComponent();
			~KinematicComponent();

			///
			///	Set the body type for physics simulation.
			///	Default Static.
			///
			void setBodyType(BodyType x);
			BodyType getBodyType() const;

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
			BodyType bodyType;
		};
	}
}
