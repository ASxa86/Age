#include <age/physics/BoxCollisionComponent.h>
#include <age/core/PimplImpl.h>

using namespace age::math;
using namespace age::physics;

class BoxCollisionComponent::Impl
{
public:
	Impl()
	{
	}

	Vector center;
	Vector size;
};

BoxCollisionComponent::BoxCollisionComponent()
{
}

BoxCollisionComponent::~BoxCollisionComponent()
{
}

void BoxCollisionComponent::setCenter(const Vector& x)
{
	this->pimpl->center = x;
}

Vector BoxCollisionComponent::getCenter() const
{
	return this->pimpl->center;
}

void BoxCollisionComponent::setSize(const Vector& x)
{
	this->pimpl->size = x;
}

Vector BoxCollisionComponent::getSize() const
{
	return this->pimpl->size;
}
