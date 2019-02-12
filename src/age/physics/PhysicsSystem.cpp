#include <age/physics/PhysicsSystem.h>

#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/core/Timer.h>
#include <age/entity/EntityEvent.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/math/Convert.h>
#include <age/math/Functions.h>
#include <age/physics/BodyComponent.h>
#include <age/physics/CollisionEvent.h>

using namespace age::core;
using namespace age::entity;
using namespace age::math;
using namespace age::physics;

class PhysicsSystem::Impl
{
public:
	struct ContactHandler : public b2ContactListener
	{
		ContactHandler(PhysicsSystem& x) : physics{x}
		{
		}

		void BeginContact(b2Contact* contact) override
		{ /* handle begin event */

			auto eidA = reinterpret_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
			auto eidB = reinterpret_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());

			// Queue the event in order for the collision to be registered outside of the b2World Step();
			// This will allow for b2 components to be modified/removed on a collision event.
			EventQueue::Instance().queueEvent(std::make_unique<CollisionEvent>(eidA, eidB));
		}
		void EndContact(b2Contact*) override
		{ /* handle end event */
		}
		void PreSolve(b2Contact*, const b2Manifold*) override
		{ /* handle pre-solve event */
		}
		void PostSolve(b2Contact*, const b2ContactImpulse*) override
		{ /* handle post-solve event */
		}

		PhysicsSystem& physics;
	};

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
	std::unique_ptr<ContactHandler> contactHandler;
};

PhysicsSystem::PhysicsSystem() : System()
{
	this->pimpl->contactHandler = std::make_unique<Impl::ContactHandler>(*this);
	this->pimpl->world.SetContactListener(this->pimpl->contactHandler.get());
	this->addFixedFunction([this](auto x) { this->frame(x); });
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::frame(std::chrono::microseconds x)
{
	const auto manager = this->getEntityManager();

	manager->each<BodyComponent, TransformComponent>([](auto&, BodyComponent& b, TransformComponent& t) {
		b.Body->SetTransform(Impl::FromVector(t.getPosition()), static_cast<float32>(t.getRotation()));
	});

	const auto seconds = std::chrono::duration_cast<age::core::seconds>(x);
	this->pimpl->world.Step(static_cast<float32>(seconds.count()), 6, 2);

	manager->each<BodyComponent, TransformComponent>([](auto&, BodyComponent& b, TransformComponent& t) {
		t.setPosition(Impl::ToVector(b.Body->GetPosition()));
		t.setRotation(Rad2Deg(b.Body->GetAngle()));

		if(b.CalculateHeading == true)
		{
			auto velocity = b.Body->GetLinearVelocity();
			velocity.Normalize();
			t.setRotation(VectorAngle({velocity.x, -velocity.y}));
		}
	});
}

b2World& PhysicsSystem::getWorld()
{
	return this->pimpl->world;
}
