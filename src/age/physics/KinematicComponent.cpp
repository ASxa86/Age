#include <age/core/Engine.h>
#include <age/core/PimplImpl.h>
#include <age/math/TransformComponent.h>
#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>

using namespace age::math;
using namespace age::physics;

KinematicComponent::KinematicComponent() : velocity{}, angularVelocity{}, bodyType{BodyType::Static}
{
}

KinematicComponent::~KinematicComponent()
{
}

void KinematicComponent::setBodyType(KinematicComponent::BodyType x)
{
	this->bodyType = x;
}

KinematicComponent::BodyType KinematicComponent::getBodyType() const
{
	return this->bodyType;
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
