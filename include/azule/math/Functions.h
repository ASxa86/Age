#pragma once

#include <azule/export.hxx>
#include <algorithm>

namespace azule
{
	class Vector;

	AZULE_EXPORT double VectorAngle(const Vector& x);
	AZULE_EXPORT double Constrain(double x, double min, double max);

	constexpr double Clamp(double x, double min, double max)
	{
		return std::max(min, std::min(x, max));
	}
}
