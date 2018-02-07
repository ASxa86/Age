#pragma once

#include <age/math/Export.h>
#include <age/math/Vector.h>

namespace age
{
	namespace math
	{
		///
		///	\class BoundingCircle
		///
		///	\brief A bounding circle for determing collisions.
		///
		///	\date February 6, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_MATH_EXPORT BoundingCircle
		{
		public:
			BoundingCircle();
			BoundingCircle(const Vector& p, double r);
			~BoundingCircle();

			///
			///	Set the position for the bounding circle.
			///	(meters)
			///
			void setPosition(const Vector& x);
			Vector getPosition() const;

			///
			///	Set the radius of the bounding circle.
			///	(meters)
			///
			void setRadius(double x);
			double getRadius() const;

		private:
			Vector position;
			double radius;
		};
	}
}
