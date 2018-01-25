#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>
#include <age/core/PimplImpl.h>
#include <age/core/Engine.h>
#include <age/math/TransformComponent.h>

using namespace age::math;
using namespace age::physics;

KinematicComponent::KinematicComponent() : velocity{}, angularVelocity{}
{
}

KinematicComponent::~KinematicComponent()
{
}

void KinematicComponent::setVelocity(const Vector& x)
{
	this->velocity = x;
}

Vector KinematicComponent::getVelocity() const
{
	return this->velocity;
}

void KinematicComponent::setAngularVelocity(double x)
{
	this->angularVelocity = x;
}

double KinematicComponent::getAngularVelocity() const
{
	return this->angularVelocity;
}
