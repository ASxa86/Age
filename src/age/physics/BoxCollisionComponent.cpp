#include <age/physics/BoxCollisionComponent.h>
#include <age/core/PimplImpl.h>

using namespace age::physics;
using namespace boost::qvm;

class BoxCollisionComponent::Impl
{
public:
	Impl()
	{
	}

	vec<double, 2> center;
	vec<double, 2> size;
};

BoxCollisionComponent::BoxCollisionComponent()
{
}

BoxCollisionComponent::~BoxCollisionComponent()
{
}

void BoxCollisionComponent::setCenter(const vec<double, 2>& x)
{
	this->pimpl->center = x;
}

vec<double, 2> BoxCollisionComponent::getCenter() const
{
	return this->pimpl->center;
}

void BoxCollisionComponent::setSize(const vec<double, 2>& x)
{
	this->pimpl->size = x;
}

vec<double, 2> BoxCollisionComponent::getSize() const
{
	return this->pimpl->size;
}
