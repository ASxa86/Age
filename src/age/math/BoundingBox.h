#pragma once

#include <age/math/Export.h>
#include <age/math/Vector.h>

namespace age
{
	namespace math
	{
		///
		///	\class BoundingBox
		///
		///	\brief An axis-aligned bounding box (AABB) for determine collisions.
		///
		///	\date February 6, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_MATH_EXPORT BoundingBox
		{
		public:
			BoundingBox();
			BoundingBox(const Vector& p, const Vector& s);
			~BoundingBox();

			///
			///	Set the position for the bounding box.
			///	(meters)
			///
			void setPosition(const Vector& x);

			///
			///	Get the position of the bounding box.
			///
			///	\return Vector The position of the bounding box (x, y).
			///
			Vector getPosition() const;

			///
			///	Set the size of the bounding box.
			///	(meters)
			///
			void setSize(const Vector& x);

			///
			///	Get the size of the bounding box.
			///
			///	\return Vector The size of the bounding box (width, height).
			///
			Vector getSize() const;

			///
			///	Get the calculated left edge of the bounding box.
			///
			double getLeft() const;

			///
			///	Get the calculate right edge of the bounding box.
			///
			double getRight() const;

			///
			///	Get the calculated top edge of the bounding box.
			///
			double getTop() const;

			///
			///	Get the calculated bottom edge of the bounding box.
			///
			double getBottom() const;

		private:
			Vector position;
			Vector size;
		};
	}
}
