#include <age/physics/KinematicComponent.h>
#include <age/physics/KinematicSystem.h>
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
		bodyDef{},
		body{nullptr}
	{
		this->bodyDef.type = b2_kinematicBody;
	}

	b2BodyDef bodyDef;
	b2Body* body;
};

KinematicComponent::KinematicComponent() : age::core::Object(), pimpl()
{
}

KinematicComponent::~KinematicComponent()
{
}

void KinematicComponent::initialize()
{
	const auto entity = this->getParent();

	if(entity != nullptr)
	{
		const auto transform = entity->getChild<TransformComponent>();

		if(transform != nullptr)
		{
			this->pimpl->bodyDef.position = Vector::To<b2Vec2, float32>(transform->getPosition());
			this->pimpl->bodyDef.angle = static_cast<float32>(transform->getRotation());
		}
	}

	const auto engine = this->getParent<age::core::Engine>(true);

	if(engine != nullptr)
	{
		const auto kSystem = engine->getChild<KinematicSystem>();

		if(kSystem != nullptr)
		{
			this->pimpl->body = kSystem->getPhysicsEngine().CreateBody(&this->pimpl->bodyDef);
		}
	}
}

void KinematicComponent::setPosition(const age::math::Vector& x)
{
	if(this->pimpl->body != nullptr)
	{
		this->pimpl->body->SetTransform(Vector::To<b2Vec2, float32>(x), this->pimpl->body->GetAngle());
	}
	else
	{
		this->pimpl->bodyDef.position = Vector::To<b2Vec2, float32>(x);
	}
}

Vector KinematicComponent::getPosition() const
{
	Vector vec;
	if(this->pimpl->body != nullptr)
	{
		const auto pos = this->pimpl->body->GetPosition();
		vec = Vector{pos.x, pos.y};
	}
	else
	{
		const auto pos = this->pimpl->bodyDef.position;
		vec = Vector{pos.x, pos.y};
	}

	return vec;
}

void KinematicComponent::setVelocity(const Vector& x)
{
	const auto vel = Vector::To<b2Vec2, float32>(x);
	if(this->pimpl->body != nullptr)
	{
		this->pimpl->body->SetLinearVelocity(vel);
	}
	else
	{
		this->pimpl->bodyDef.linearVelocity = vel;
	}
}

Vector KinematicComponent::getVelocity() const
{
	Vector vec;
	if (this->pimpl->body != nullptr)
	{
		const auto pos = this->pimpl->body->GetLinearVelocity();
		vec = Vector{pos.x, pos.y};
	}
	else
	{
		const auto pos = this->pimpl->bodyDef.linearVelocity;
		vec = Vector{pos.x, pos.y};
	}

	return vec;
}

void KinematicComponent::setRotation(double x)
{
	const auto pi = 3.14 / 180.0;
	if(this->pimpl->body != nullptr)
	{
		this->pimpl->body->SetTransform(this->pimpl->body->GetPosition(), static_cast<float32>(x * pi));
	}
	else
	{
		this->pimpl->bodyDef.angle = static_cast<float32>(x * pi);
	}
}

double KinematicComponent::getRotation() const
{
	auto rotation = 0.0;
	const auto pi = 3.14 / 180.0;

	if(this->pimpl->body != nullptr)
	{
		rotation = this->pimpl->body->GetAngle() / pi;
	}
	else
	{
		rotation =  this->pimpl->bodyDef.angle / pi;
	}

	return rotation;
}

void KinematicComponent::setAngularVelocity(double x)
{
	if(this->pimpl->body != nullptr)
	{
		this->pimpl->body->SetAngularVelocity(static_cast<float32>(x));
	}
	else
	{
		this->pimpl->bodyDef.angularVelocity = static_cast<float32>(x);
	}
}

double KinematicComponent::getAngularVelocity() const
{
	auto velocity = 0.0;

	if(this->pimpl->body != nullptr)
	{
		velocity = this->pimpl->body->GetAngularVelocity();
	}
	else
	{
		velocity = this->pimpl->bodyDef.angularVelocity;
	}

	return velocity;
}
