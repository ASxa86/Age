#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>
#include <age/core/PimplImpl.h>
#include <age/core/Engine.h>
#include <age/math/TransformComponent.h>

using namespace age::math;
using namespace age::physics;

KinematicComponent::KinematicComponent()
{
}

KinematicComponent::~KinematicComponent()
{
}

void KinematicComponent::setPosition(const Vector& x)
{
	this->position = x;
}

Vector KinematicComponent::getPosition() const
{
	return this->position;
}

void KinematicComponent::setVelocity(const Vector& x)
{
	this->velocity = x;
}

Vector KinematicComponent::getVelocity() const
{
	return this->velocity;
}

void KinematicComponent::setRotation(double x)
{
	this->rotation = x;
}

double KinematicComponent::getRotation() const
{
	return this->rotation;
}

void KinematicComponent::setAngularVelocity(double x)
{
	this->angularVelocity = x;
}

double KinematicComponent::getAngularVelocity() const
{
	return this->angularVelocity;
}
