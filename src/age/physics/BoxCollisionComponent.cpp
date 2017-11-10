#include <age/physics/BoxCollisionComponent.h>

using namespace age::physics;
using namespace boost::qvm;

BoxCollisionComponent::BoxCollisionComponent()
{
}

BoxCollisionComponent::~BoxCollisionComponent()
{
}

void BoxCollisionComponent::setCenter(const vec<double, 2>& x)
{
	this->center = x;
}

vec<double, 2> BoxCollisionComponent::getCenter() const
{
	return this->center;
}

void BoxCollisionComponent::setSize(const vec<double, 2>& x)
{
	this->size = x;
}

vec<double, 2> BoxCollisionComponent::getSize() const
{
	return this->size;
}
