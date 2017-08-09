#include <age/physics/KinematicComponent.h>
#include <age/core/PimplImpl.h>

using namespace age::math;
using namespace age::physics;

class KinematicComponent::Impl
{
public:
	Impl() :
		velocity{},
		angularVelocity{}
	{
	}

	Vector velocity;
	double angularVelocity;
};

KinematicComponent::KinematicComponent()
{
}

KinematicComponent::~KinematicComponent()
{
}

void KinematicComponent::setVelocity(const Vector& x)
{
	this->pimpl->velocity = x;
}

Vector KinematicComponent::getVelocity() const
{
	return this->pimpl->velocity;
}

void KinematicComponent::setAngularVelocity(double x)
{
	this->pimpl->angularVelocity = x;
}

double KinematicComponent::getAngularVelocity() const
{
	return this->pimpl->angularVelocity;
}
