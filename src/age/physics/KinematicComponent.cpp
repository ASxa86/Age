#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>
#include <age/core/PimplImpl.h>
#include <age/core/Engine.h>
#include <age/math/TransformComponent.h>
#include <age/physics/Box2D/Dynamics/b2Body.h>
#include <age/physics/Box2D/Dynamics/b2World.h>

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

void KinematicComponent::setPosition(const age::math::Vector& x)
{
	this->pimpl->body->SetTransform(Vector::To<b2Vec2, float32>(x * this->pimpl->scale), this->pimpl->body->GetAngle());
}

Vector KinematicComponent::getPosition() const
{
	const auto pos = this->pimpl->body->GetPosition();
	return Vector{pos.x, pos.y} / this->pimpl->scale;
}

void KinematicComponent::setVelocity(const Vector& x)
{
	this->pimpl->body->SetLinearVelocity(Vector::To<b2Vec2, float32>(x * this->pimpl->scale));
}

Vector KinematicComponent::getVelocity() const
{
	const auto pos = this->pimpl->body->GetLinearVelocity();
	return Vector{pos.x, pos.y} / this->pimpl->scale;
}

void KinematicComponent::setRotation(double x)
{
	this->pimpl->body->SetTransform(this->pimpl->body->GetPosition(), static_cast<float32>(x * b2_pi / 180.0));
}

double KinematicComponent::getRotation() const
{
	return this->pimpl->body->GetAngle() / b2_pi * 180.0;
}

void KinematicComponent::setAngularVelocity(double x)
{
	this->pimpl->body->SetAngularVelocity(static_cast<float32>(x));
}

double KinematicComponent::getAngularVelocity() const
{
	return this->pimpl->body->GetAngularVelocity();
}
