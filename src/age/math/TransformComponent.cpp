#include <age/math/TransformComponent.h>
#include <age/core/PimplImpl.h>

using namespace age::core;
using namespace age::math;

class TransformComponent::Impl
{
public:
	Impl() :
		position{},
		rotation{}
	{
	}

	Vector position;
	double rotation;
};

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::setPosition(const Vector& x)
{
	this->pimpl->position = x;
}

Vector TransformComponent::getPosition() const
{
	return this->pimpl->position;
}

void TransformComponent::setRotation(double x)
{
	// Clamp the angle between 0.0 and 360.0.
	x = std::fmod(x, 360.0);
	if(x < 0.0) x += 360.0;
	this->pimpl->rotation = x;
}

double TransformComponent::getRotation() const
{
	return this->pimpl->rotation;
}
