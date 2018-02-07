#pragma once

#include <age/math/Export.h>

namespace age
{
	namespace math
	{
		class BoundingBox;
		class BoundingCircle;

		AGE_MATH_EXPORT bool intersect(const BoundingBox& a, const BoundingBox& b);
		AGE_MATH_EXPORT bool intersect(const BoundingCircle& a, const BoundingCircle& b);
		AGE_MATH_EXPORT bool intersect(const BoundingBox& a, const BoundingCircle& b);
	}
}
