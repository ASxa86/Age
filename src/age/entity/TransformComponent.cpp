#include <age/entity/TransformComponent.h>
#include <cmath>

using namespace age::entity;

TransformComponent::TransformComponent() : position{}, rotation{}
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::setPosition(const age::math::Vector& x)
{
	this->position = x;
}

age::math::Vector TransformComponent::getPosition() const
{
	return this->position;
}

void TransformComponent::setRotation(double x)
{
	x = std::fmod(x, 360.0);
	if(x < 0.0)
		x += 360.0;
	this->rotation = x;
}

double TransformComponent::getRotation() const
{
	return this->rotation;
}
