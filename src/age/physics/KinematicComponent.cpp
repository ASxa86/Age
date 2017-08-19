#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>
#include <age/core/PimplImpl.h>
#include <age/core/Engine.h>
#include <age/math/TransformComponent.h>
#include <age/physics/Box2D/Dynamics/b2Body.h>
#include <age/physics/Box2D/Dynamics/b2World.h>
#include <boost/qvm/vec_access.hpp>
#include <boost/qvm/vec_operations.hpp>
#include <boost/math/constants/constants.hpp>

using namespace boost::qvm;
using namespace age::math;
using namespace age::physics;

class KinematicComponent::Impl
{
public:
	Impl() :
		body{nullptr}
	{
		b2BodyDef def;
		def.type = b2_kinematicBody;
		this->body = PhysicsSystem::Engine().CreateBody(&def);
	}

	~Impl()
	{
		PhysicsSystem::Engine().DestroyBody(this->body);
	}

	double scale = 1.0 / 32.0;

	b2Body* body;
};

KinematicComponent::KinematicComponent() : age::core::Object(), pimpl()
{
}

KinematicComponent::~KinematicComponent()
{
}

void KinematicComponent::setPosition(const vec<double, 2>& x)
{
	const auto pos = x * this->pimpl->scale;
	const auto transform = b2Vec2{static_cast<float32>(X(pos)), static_cast<float32>(Y(pos))};
	this->pimpl->body->SetTransform(transform, this->pimpl->body->GetAngle());
}

vec<double, 2> KinematicComponent::getPosition() const
{
	const auto pos = this->pimpl->body->GetPosition();
	return vec<double, 2>{pos.x, pos.y} / this->pimpl->scale;
}

void KinematicComponent::setVelocity(const vec<double, 2>& x)
{
	const auto v = x * this->pimpl->scale;
	const auto vel = b2Vec2{ static_cast<float32>(X(v)), static_cast<float32>(Y(v)) };
	this->pimpl->body->SetLinearVelocity(vel);
}

vec<double, 2> KinematicComponent::getVelocity() const
{
	const auto pos = this->pimpl->body->GetLinearVelocity();
	return vec<double, 2>{pos.x, pos.y} / this->pimpl->scale;
}

void KinematicComponent::setRotation(double x)
{
	const auto angle = static_cast<float32>(x * boost::math::constants::pi<double>() / 180.0);
	this->pimpl->body->SetTransform(this->pimpl->body->GetPosition(), angle);
}

double KinematicComponent::getRotation() const
{
	return this->pimpl->body->GetAngle() / boost::math::constants::pi<double>() * 180.0;
}

void KinematicComponent::setAngularVelocity(double x)
{
	this->pimpl->body->SetAngularVelocity(static_cast<float32>(x));
}

double KinematicComponent::getAngularVelocity() const
{
	return this->pimpl->body->GetAngularVelocity();
}
