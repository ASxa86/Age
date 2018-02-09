#pragma once

#include <age/math/Vector.h>
#include <age/physics/Export.h>

namespace age
{
	namespace physics
	{
		///
		///	\class CircleCollisionComponent
		///
		///	\brief A circle collision component for determining if this object collides with another.
		///
		///	\date February 8, 2017
		///
		///	\date Aaron Shelley
		///
		class AGE_PHYSICS_EXPORT CircleCollisionComponent
		{
		public:
			CircleCollisionComponent();
			~CircleCollisionComponent();

			///
			///	Set the center of this collision component. This is an offset to the entity it is attached to.
			///
			void setCenter(const age::math::Vector& x);
			age::math::Vector getCenter() const;

			///
			///	Set the size of the box (x:width, y:height).
			///
			void setRadius(double x);
			double getRadius() const;

		private:
			age::math::Vector center;
			double radius;
		};
	}
}
