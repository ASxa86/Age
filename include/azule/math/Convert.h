#pragma once

#include <azule/math/Constants.h>
#include <azule/export.h>

namespace azule
{
	namespace math
	{
		constexpr double Deg2Rad(double x) noexcept
		{
			return x * (PI / 180.0);
		}

		constexpr double Rad2Deg(double x) noexcept
		{
			return x * (180.0 / PI);
		}
	}
}
