#include <azule/math/Functions.h>

#include <azule/math/Convert.h>
#include <azule/math/Vector.h>
#include <cmath>

double azule::math::VectorAngle(const azule::math::Vector& x)
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

double azule::math::Constrain(double x, double min, double max)
{
	if(x < min || x > max)
	{
		const auto t = (x - min) / (max - min);
		return min + (max - min) * (t - std::floor(t));
	}

	return x;
}
