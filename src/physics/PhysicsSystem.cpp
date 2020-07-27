#include <azule/physics/PhysicsSystem.h>

#include <Box2D/Box2D.h>
#include <azule/core/EventQueue.h>
#include <azule/core/Timer.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/EntityEvent.h>
#include <azule/entity/TransformComponent.h>
#include <azule/math/Convert.h>
#include <azule/math/Functions.h>
#include <azule/physics/BoxCollisionComponent.h>
#include <azule/physics/CircleCollisionComponent.h>
#include <azule/physics/CollisionEvent.h>
#include <azule/physics/EdgeCollisionComponent.h>
#include <azule/physics/KinematicComponent.h>
#include <azule/utilities/PimplImpl.h>
#include <azule/utilities/Signal.h>

using namespace azule::core;
using namespace azule::entity;
using namespace azule::math;
using namespace azule::physics;

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
			EventQueue::Instance().queueEvent(std::make_unique<CollisionEvent>(*eidA, *eidB));
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

	static azule::math::Vector ToVector(const b2Vec2& x)
	{
		return {x.x, x.y};
	}

	static b2Vec2 FromVector(const azule::math::Vector& x)
	{
		return {static_cast<float32>(x.X), static_cast<float32>(x.Y)};
	}

	b2Body* getOrCreateBody(Entity* x)
	{
		for(auto body = this->world.GetBodyList(); body != nullptr; body = body->GetNext())
		{
			if(x == body->GetUserData())
			{
				return body;
			}
		}

		b2BodyDef bdef{};
		auto body = this->world.CreateBody(&bdef);
		body->SetUserData(const_cast<void*>(reinterpret_cast<const void*>(x)));
		return body;
	}

	void configureBody2D(b2Body* b, KinematicComponent& k)
	{
		b->SetLinearVelocity(Impl::FromVector(k.LinearVelocity));

		switch(k.BodyType)
		{
			case KinematicComponent::Type::Static:
				b->SetType(b2BodyType::b2_staticBody);
				break;

			case KinematicComponent::Type::Kinematic:
				b->SetType(b2BodyType::b2_kinematicBody);
				break;

			case KinematicComponent::Type::Dynamic:
				b->SetType(b2BodyType::b2_dynamicBody);
				break;

			default:
				break;
		}
	}

	void configureBody2D(b2Body* b, TransformComponent& t)
	{
		b->SetTransform(Impl::FromVector(t.Position), static_cast<float32>(t.Rotation));
	}

	void configureBodyAge(b2Body* b, KinematicComponent& k)
	{
		k.LinearVelocity = Impl::ToVector(b->GetLinearVelocity());
	}

	void configureBodyAge(b2Body* b, TransformComponent& t)
	{
		t.Position = Impl::ToVector(b->GetPosition());
		t.Rotation = b->GetAngle();
	}

	void addBody(Entity* x)
	{
		auto kinematic = x->getChild<KinematicComponent>();

		auto body = this->getOrCreateBody(x);
		this->configureBody2D(body, *kinematic);
	}

	void removeBody(Entity* e)
	{
		auto body = this->getOrCreateBody(e);
		this->world.DestroyBody(body);
	}

	void configureFixture(b2Fixture* f, CollisionComponent& c)
	{
		f->SetDensity(static_cast<float32>(c.Density));
		f->SetRestitution(static_cast<float32>(c.Restitution));
		f->SetFriction(static_cast<float32>(c.Friction));
		f->SetSensor(c.IsSensor);
	}

	void configureBox2D(b2Fixture* f, BoxCollisionComponent& b)
	{
		auto shape = static_cast<b2PolygonShape*>(f->GetShape());
		shape->SetAsBox(static_cast<float32>(b.Width / 2.0), static_cast<float32>(b.Height / 2.0));
		this->configureFixture(f, b);
	}

	void configureCircle2D(b2Fixture* f, CircleCollisionComponent& c)
	{
		auto shape = static_cast<b2CircleShape*>(f->GetShape());
		shape->m_radius = static_cast<float32>(c.Radius);
		this->configureFixture(f, c);
	}

	void configureEdge2D(b2Fixture* f, EdgeCollisionComponent& e)
	{
		auto shape = static_cast<b2EdgeShape*>(f->GetShape());
		shape->Set(FromVector(e.Vertex1), FromVector(e.Vertex2));
		this->configureFixture(f, e);
	}

	void addBox(Entity* x)
	{
		auto box = x->getChild<BoxCollisionComponent>();

		b2FixtureDef fdef{};
		b2PolygonShape shape{};
		fdef.shape = &shape;
		auto body = this->getOrCreateBody(x);
		auto fixture = body->CreateFixture(&fdef);

		this->configureBox2D(fixture, *box);
	}

	void addCircle(Entity* x)
	{
		auto circle = x->getChild<CircleCollisionComponent>();
		b2FixtureDef fdef{};
		b2CircleShape shape{};
		fdef.shape = &shape;
		auto body = this->getOrCreateBody(x);
		auto fixture = body->CreateFixture(&fdef);
		this->configureCircle2D(fixture, *circle);
	}

	void addEdge(Entity* x)
	{
		auto edge = x->getChild<EdgeCollisionComponent>();
		b2FixtureDef fdef{};
		b2EdgeShape shape{};
		fdef.shape = &shape;
		auto body = this->getOrCreateBody(x);
		auto fixture = body->CreateFixture(&fdef);
		this->configureEdge2D(fixture, *edge);
	}

	void removeFixture(Entity* x)
	{
		auto body = this->getOrCreateBody(x);
		body->DestroyFixture(body->GetFixtureList());
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

void PhysicsSystem::onStartup()
{
	const auto processEntity = [this](Entity* e) {
		if(e->getChild<KinematicComponent>() != nullptr)
		{
			this->pimpl->addBody(e);
		}

		if(e->getChild<BoxCollisionComponent>() != nullptr)
		{
			this->pimpl->addBox(e);
		}

		if(e->getChild<CircleCollisionComponent>() != nullptr)
		{
			this->pimpl->addCircle(e);
		}

		if(e->getChild<EdgeCollisionComponent>() != nullptr)
		{
			this->pimpl->addEdge(e);
		}
	};

	this->track(EventQueue::Instance().addEventHandler([this, processEntity](auto evt) {
		const auto entityEvt = dynamic_cast<EntityEvent*>(evt);

		if(entityEvt != nullptr)
		{
			switch(entityEvt->getType())
			{
				case EntityEvent::Type::EntityAdded:
					processEntity(entityEvt->getEntity());
					break;

				case EntityEvent::Type::EntityRemoved:
				{
					this->pimpl->removeBody(entityEvt->getEntity());
				}
				break;

				case EntityEvent::Type::ComponentAdded:
				{
					if(dynamic_cast<KinematicComponent*>(entityEvt->Component) != nullptr)
					{
						this->pimpl->addBody(entityEvt->getEntity());
					}
					else if(dynamic_cast<BoxCollisionComponent*>(entityEvt->Component) != nullptr)
					{
						this->pimpl->addBox(entityEvt->getEntity());
					}
					else if(dynamic_cast<CircleCollisionComponent*>(entityEvt->Component) != nullptr)
					{
						this->pimpl->addCircle(entityEvt->getEntity());
					}
				}
				break;

				case EntityEvent::Type::ComponentRemoved:
				{
					if(dynamic_cast<KinematicComponent*>(entityEvt->Component) != nullptr)
					{
						this->pimpl->removeBody(entityEvt->getEntity());
					}
					else if(dynamic_cast<BoxCollisionComponent*>(entityEvt->Component) != nullptr
							|| dynamic_cast<CircleCollisionComponent*>(entityEvt->Component) != nullptr
							|| dynamic_cast<EdgeCollisionComponent*>(entityEvt->Component) != nullptr)
					{
						this->pimpl->removeFixture(entityEvt->getEntity());
					}
				}
				break;
			}
		}
	}));

	// Initialize all entities that have been configured before running the engine.
	// Any entities or components added/removed will be handled by the event handler beyond this point.
	const auto manager = this->getEntityDatabase();

	if(manager != nullptr)
	{
		for(auto e : manager->getChildren<Entity>())
		{
			processEntity(e);
		}
	}
}

void PhysicsSystem::frame(std::chrono::microseconds x)
{
	for(auto body = this->pimpl->world.GetBodyList(); body != nullptr; body = body->GetNext())
	{
		auto entity = reinterpret_cast<Entity*>(body->GetUserData());

		if(entity->getChild<KinematicComponent>() != nullptr)
		{
			this->pimpl->configureBody2D(body, *entity->getChild<KinematicComponent>());
		}

		if(entity->getChild<BoxCollisionComponent>() != nullptr)
		{
			this->pimpl->configureBox2D(body->GetFixtureList(), *entity->getChild<BoxCollisionComponent>());
		}

		if(entity->getChild<CircleCollisionComponent>() != nullptr)
		{
			this->pimpl->configureCircle2D(body->GetFixtureList(), *entity->getChild<CircleCollisionComponent>());
		}

		if(entity->getChild<EdgeCollisionComponent>() != nullptr)
		{
			this->pimpl->configureEdge2D(body->GetFixtureList(), *entity->getChild<EdgeCollisionComponent>());
		}

		if(entity->getChild<TransformComponent>() != nullptr)
		{
			this->pimpl->configureBody2D(body, *entity->getChild<TransformComponent>());
		}
	}

	const auto seconds = std::chrono::duration_cast<azule::core::seconds>(x);
	this->pimpl->world.Step(static_cast<float32>(seconds.count()), 6, 2);

	for(auto body = this->pimpl->world.GetBodyList(); body != nullptr; body = body->GetNext())
	{
		auto entity = reinterpret_cast<Entity*>(body->GetUserData());

		if(entity->getChild<KinematicComponent>() != nullptr)
		{
			this->pimpl->configureBodyAge(body, *entity->getChild<KinematicComponent>());
		}

		if(entity->getChild<TransformComponent>() != nullptr)
		{
			this->pimpl->configureBodyAge(body, *entity->getChild<TransformComponent>());
		}

		if(entity->getChild<KinematicComponent>() != nullptr && entity->getChild<TransformComponent>() != nullptr)
		{
			auto k = entity->getChild<KinematicComponent>();
			auto t = entity->getChild<TransformComponent>();

			if(k->CalculateHeading == true)
			{
				t->Rotation = VectorAngle({k->LinearVelocity.X, -k->LinearVelocity.Y});
			}
		}
	}
}
