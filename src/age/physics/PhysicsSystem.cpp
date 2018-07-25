#ifdef WIN32
// Setting an int as void* for UserData within b2body
#pragma warning(disable : 4311 4312 4302)
#endif

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/core/Timer.h>
#include <age/entity/EntityEvent.h>
#include <age/entity/EntityManager.h>
#include <age/math/TransformComponent.h>
#include <age/physics/BodyComponent.h>
#include <age/physics/PhysicsSystem.h>

using namespace age::core;
using namespace age::entity;
using namespace age::math;
using namespace age::physics;

class PhysicsSystem::Impl
{
public:
	Impl() : world{{0.0, 0.0}}
	{
	}

	static age::math::Vector ToVector(const b2Vec2& x)
	{
		return {x.x, x.y};
	}

	static b2Vec2 FromVector(const age::math::Vector& x)
	{
		return {static_cast<float32>(x.getX()), static_cast<float32>(x.getY())};
	}

	b2World world;
};

PhysicsSystem::PhysicsSystem() : System()
{
	this->addFixedFunction([this](auto x) { this->frame(x); });
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::frame(std::chrono::microseconds x)
{
	const auto seconds = std::chrono::duration_cast<age::core::seconds>(x);

	const auto manager = this->getEntityManager();

	manager->each<BodyComponent, TransformComponent>([](auto, BodyComponent& b, TransformComponent& t) {
		b.body->SetTransform(Impl::FromVector(t.getPosition()), static_cast<float32>(t.getRotation()));
	});

	this->pimpl->world.Step(static_cast<float32>(seconds.count()), 6, 2);

	manager->each<BodyComponent, TransformComponent>([](auto, BodyComponent& b, TransformComponent& t) {
		t.setPosition(Impl::ToVector(b.body->GetPosition()));
		t.setRotation(b.body->GetAngle());
	});
}

b2World& PhysicsSystem::getWorld()
{
	return this->pimpl->world;
}
