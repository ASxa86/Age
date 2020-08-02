#include <azule/math/Functions.h>

#include <azule/math/Convert.h>
#include <azule/math/Vector.h>
#include <cmath>

double azule::VectorAngle(const glm::vec2& x)
{
	if(glm::length(x) > 0.0)
	{
		// 0 = arccos(a * b / |a| * |b|)
		const glm::vec2 y_axis{0.0, 1.0};
		auto angle = glm::degrees(std::acos((glm::dot(y_axis, x) / (glm::length(y_axis) * glm::length(x)))));

		if(x.x < 0.0)
		{
			angle = 360.0f - angle;
		}

		return angle;
	}

	return 0.0;
}

double azule::Constrain(double x, double min, double max)
{
	if(x < min || x > max)
	{
		const auto t = (x - min) / (max - min);
		return min + (max - min) * (t - std::floor(t));
	}

	return x;
}
