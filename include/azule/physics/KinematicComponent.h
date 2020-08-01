#pragma once

#include <azule/entity/Component.h>
#include <azule/export.hxx>
#include <azule/math/Vector.h>

namespace azule
{
	struct AZULE_EXPORT KinematicComponent : public azule::Component
	{
		///
		///	\enum BodyType
		///
		///	\brief Describes how this component is processed during physics calculations.
		///
		enum class Type : int
		{
			/// A static body does not move under simulation and behaves as if it has infinite mass.Internally, Box2D
			/// stores zero for the mass and the inverse mass. Static bodies can be moved manually by the user. A static
			/// body has zero velocity. Static bodies do not collide with other static or kinematic bodies.
			Static,

			/// A kinematic body moves under simulation according to its velocity.Kinematic bodies do not respond to
			/// forces. They can be moved manually by the user, but normally a kinematic body is moved by setting its
			/// velocity. A kinematic body behaves as if it has infinite mass, however, Box2D stores zero for the mass
			/// and the inverse mass.Kinematic bodies do not collide with other kinematic or static bodies
			Kinematic,

			/// A dynamic body is fully simulated.They can be moved manually by the user, but normally they move
			/// according to forces. A dynamic body can collide with all body types. A dynamic body always has finite,
			/// non - zero mass. If you try to set the mass of a dynamic body to zero, it will automatically acquire a mass
			/// of one kilogram and it won’t rotate.
			Dynamic
		};

		KinematicComponent();

		/// The component velocity to describe an entity.
		azule::Vector LinearVelocity{};

		/// The body type to describe this an entity.
		Type BodyType;

		/// Enable to calculate heading rotation for an entity.
		/// This will cause any rotations on an associated TransformComponent to be overwritten.
		bool CalculateHeading{false};
	};
}
