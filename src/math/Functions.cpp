#include <age/math/Functions.h>

#include <age/math/Convert.h>
#include <age/math/Vector.h>
#include <cmath>

double age::math::VectorAngle(const age::math::Vector& x)
{
	if(x.magnitude() > 0.0)
	{
		// 0 = arccos(a * b / |a| * |b|)
		const Vector y_axis{0.0, 1.0};
		auto angle = Rad2Deg(std::acos((y_axis * x) / (y_axis.magnitude() * x.magnitude())));

		if(x.X < 0.0)
		{
			angle = 360.0 - angle;
		}

		return angle;
	}

	return 0.0;
}

double age::math::Constrain(double x, double min, double max)
{
	if(x < min || x > max)
	{
		const auto t = (x - min) / (max - min);
		return min + (max - min) * (t - std::floor(t));
	}

	return x;
}
