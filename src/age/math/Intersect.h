#pragma once

#include <age/math/Export.h>

namespace age
{
	namespace math
	{
		class BoundingBox;
		class BoundingCircle;

		///
		///	\brief Axis Aligned Bounding Box intersect detection.
		///
		AGE_MATH_EXPORT bool intersect(const BoundingBox& a, const BoundingBox& b);

		///
		///	\brief Circle intersect detection.
		///
		AGE_MATH_EXPORT bool intersect(const BoundingCircle& a, const BoundingCircle& b);

		///
		///	\brief Axis Aligned Bounding Box and Circle intersect detection.
		///
		AGE_MATH_EXPORT bool intersect(const BoundingBox& a, const BoundingCircle& b);
	}
}
