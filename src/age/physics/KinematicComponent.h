#pragma once

#include <age/math/Vector.h>
#include <age/physics/Export.h>

namespace age
{
	namespace physics
	{
		struct KinematicComponent
		{
			///
			///	\enum BodyType
			///
			///	\brief Describes how this component is processed during physics calculations.
			///
			enum class BodyType : int
			{
				/// zero mass, zero velocity, may be manually moved
				Static,

				/// zero mass, non-zero velocity set by user, moved by solver
				Kinematic,

				/// positive mass, non-zero velocity determined by forces, moved by solver
				Dynamic
			};

			age::math::Vector LinearVelocity;
			BodyType BodyType;
		};
	}
}
