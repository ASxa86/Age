#include <age/physics/KinematicComponent.h>
#include <age/core/PimplImpl.h>

using namespace age::physics;

class KinematicComponent::Impl
{
public:
	Impl() :
		velocity{},
		angularVelocity{}
	{
	}

	std::array<double, 2> velocity;
	double angularVelocity;
};

KinematicComponent::KinematicComponent()
{
}

KinematicComponent::~KinematicComponent()
{
}

void KinematicComponent::setVelocity(const std::array<double, 2>& x)
{
	this->pimpl->velocity = x;
}

std::array<double, 2> KinematicComponent::getVelocity() const
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
