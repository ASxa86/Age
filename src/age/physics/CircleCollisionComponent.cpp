#include <age/physics/CircleCollisionComponent.h>

using namespace age::math;
using namespace age::physics;

CircleCollisionComponent::CircleCollisionComponent()
{
}

CircleCollisionComponent::~CircleCollisionComponent()
{
}

void CircleCollisionComponent::setCenter(const Vector& x)
{
	this->center = x;
}

Vector CircleCollisionComponent::getCenter() const
{
	return this->center;
}

void CircleCollisionComponent::setRadius(double x)
{
	this->radius = x;
}

double CircleCollisionComponent::getRadius() const
{
	return this->radius;
}
