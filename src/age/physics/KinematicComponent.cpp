#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>
#include <age/core/PimplImpl.h>
#include <age/core/Engine.h>
#include <age/math/TransformComponent.h>
#include <boost/qvm/vec_access.hpp>
#include <boost/qvm/vec_operations.hpp>
#include <boost/math/constants/constants.hpp>

using namespace boost::qvm;
using namespace age::math;
using namespace age::physics;

KinematicComponent::KinematicComponent()
{
}

KinematicComponent::~KinematicComponent()
{
}

void KinematicComponent::setPosition(const vec<double, 2>& x)
{
	this->position = x;
}

vec<double, 2> KinematicComponent::getPosition() const
{
	return this->position;
}

void KinematicComponent::setVelocity(const vec<double, 2>& x)
{
	this->velocity = x;
}

vec<double, 2> KinematicComponent::getVelocity() const
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
