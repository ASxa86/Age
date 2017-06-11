#include <age/core/TransformComponent.h>
#include <age/core/PimplImpl.h>

using namespace age::core;

class TransformComponent::Impl
{
public:
	Impl() :
		position{},
		rotation{}
	{
	}

	std::array<double, 2> position;
	double rotation;
};

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::setPosition(const std::array<double, 2>& x)
{
	this->pimpl->position = x;
}

std::array<double, 2> TransformComponent::getPosition() const
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
