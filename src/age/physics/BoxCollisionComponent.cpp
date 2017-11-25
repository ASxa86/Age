#include <age/physics/BoxCollisionComponent.h>

using namespace age::math;
using namespace age::physics;

BoxCollisionComponent::BoxCollisionComponent()
{
}

BoxCollisionComponent::~BoxCollisionComponent()
{
}

void BoxCollisionComponent::setCenter(const Vector& x)
{
	this->center = x;
}

Vector BoxCollisionComponent::getCenter() const
{
	return this->center;
}

void BoxCollisionComponent::setSize(const Vector& x)
{
	this->size = x;
}

Vector BoxCollisionComponent::getSize() const
{
	return this->size;
}
