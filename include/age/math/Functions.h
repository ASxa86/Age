#pragma once

#include <age/math/export.h>
#include <algorithm>

namespace age
{
	namespace math
	{
		class Vector;

		AGE_MATH_EXPORT double VectorAngle(const Vector& x);
		AGE_MATH_EXPORT double Constrain(double x, double min, double max);

		constexpr double Clamp(double x, double min, double max)
		{
			return std::max(min, std::min(x, max));
		}

	}
}
