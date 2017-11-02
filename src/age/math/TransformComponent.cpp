#include <age/math/TransformComponent.h>
#include <cmath>

using namespace age::math;
using namespace boost::qvm;

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::setPosition(const vec<double, 2>& x)
{
	this->position = x;
}

vec<double, 2> TransformComponent::getPosition() const
{
	return this->position;
}

void TransformComponent::setRotation(double x)
{
	x = std::fmod(x, 360.0);
	if (x < 0.0) x += 360.0;
	this->rotation = x;
}

double TransformComponent::getRotation() const
{
	return this->rotation;
}
