#pragma once

#include <azule/math/Vector.h>
#include <algorithm>
#include <azule/export.hxx>

namespace azule
{
	AZULE_EXPORT double VectorAngle(const glm::vec2& x);
	AZULE_EXPORT double Constrain(double x, double min, double max);

	constexpr double Clamp(double x, double min, double max)
	{
		return std::max(min, std::min(x, max));
	}
}
