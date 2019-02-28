#include <age/physics/PhysicsSystem.h>

#include <Box2D/Box2D.h>
#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/core/Timer.h>
#include <age/entity/EntityEvent.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/math/Convert.h>
#include <age/math/Functions.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/CircleCollisionComponent.h>
#include <age/physics/CollisionEvent.h>
#include <age/physics/EdgeCollisionComponent.h>
#include <age/physics/KinematicComponent.h>

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

	static age::math::Vector ToVector(const b2Vec2& x)
	{
		return {x.x, x.y};
	}

	static b2Vec2 FromVector(const age::math::Vector& x)
	{
		return {static_cast<float32>(x.X), static_cast<float32>(x.Y)};
	}

	b2Body* getOrCreateBody(const Entity& x)
	{
		for(auto body = this->world.GetBodyList(); body != nullptr; body = body->GetNext())
		{
			if(&x == body->GetUserData())
			{
				return body;
			}
		}

		b2BodyDef bdef{};
		auto body = this->world.CreateBody(&bdef);
		body->SetUserData(const_cast<void*>(reinterpret_cast<const void*>(&x)));
		return body;
	}

	void configureBody2D(b2Body* b, KinematicComponent& k)
	{
		b->SetLinearVelocity(Impl::FromVector(k.LinearVelocity));

		switch(k.BodyType)
		{
			case KinematicComponent::BodyType::Static:
				b->SetType(b2BodyType::b2_staticBody);
				break;

			case KinematicComponent::BodyType::Kinematic:
				b->SetType(b2BodyType::b2_kinematicBody);
				break;

			case KinematicComponent::BodyType::Dynamic:
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

	void addBody(const Entity& x)
	{
		auto& kinematic = x.getComponent<KinematicComponent>();

		auto body = this->getOrCreateBody(x);
		this->configureBody2D(body, kinematic);
	}

	void removeBody(const Entity& e)
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

	void addBox(const Entity& x)
	{
		auto& box = x.getComponent<BoxCollisionComponent>();

		b2FixtureDef fdef{};
		b2PolygonShape shape{};
		fdef.shape = &shape;
		auto body = this->getOrCreateBody(x);
		auto fixture = body->CreateFixture(&fdef);

		this->configureBox2D(fixture, box);
	}

	void addCircle(const Entity& x)
	{
		auto& circle = x.getComponent<CircleCollisionComponent>();
		b2FixtureDef fdef{};
		b2CircleShape shape{};
		fdef.shape = &shape;
		auto body = this->getOrCreateBody(x);
		auto fixture = body->CreateFixture(&fdef);
		this->configureCircle2D(fixture, circle);
	}

	void addEdge(const Entity& x)
	{
		auto& edge = x.getComponent<EdgeCollisionComponent>();
		b2FixtureDef fdef{};
		b2EdgeShape shape{};
		fdef.shape = &shape;
		auto body = this->getOrCreateBody(x);
		auto fixture = body->CreateFixture(&fdef);
		this->configureEdge2D(fixture, edge);
	}

	void removeFixture(const Entity& x)
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

void PhysicsSystem::initialize()
{
	EventQueue::Instance().addEventHandler([this](auto evt) {
		const auto entityEvt = dynamic_cast<EntityEvent*>(evt);

		if(entityEvt != nullptr)
		{
			switch(entityEvt->getType())
			{
				case EntityEvent::Type::EntityRemoved:
				{
					this->pimpl->removeBody(entityEvt->getEntity());
				}
				break;

				case EntityEvent::Type::ComponentAdded:
				{
					if(entityEvt->getComponent<KinematicComponent>() != nullptr)
					{
						this->pimpl->addBody(entityEvt->getEntity());
					}
					else if(entityEvt->getComponent<BoxCollisionComponent>() != nullptr)
					{
						this->pimpl->addBox(entityEvt->getEntity());
					}
					else if(entityEvt->getComponent<CircleCollisionComponent>() != nullptr)
					{
						this->pimpl->addCircle(entityEvt->getEntity());
					}
				}
				break;

				case EntityEvent::Type::ComponentRemoved:
				{
					if(entityEvt->getComponent<KinematicComponent>() != nullptr)
					{
						this->pimpl->removeBody(entityEvt->getEntity());
					}
					else if(entityEvt->getComponent<BoxCollisionComponent>() != nullptr
							|| entityEvt->getComponent<CircleCollisionComponent>() != nullptr
							|| entityEvt->getComponent<EdgeCollisionComponent>() != nullptr)
					{
						this->pimpl->removeFixture(entityEvt->getEntity());
					}
				}
				break;
			}
		}
	});

	// Initialize all entities that have been configured before running the engine.
	// Any entities or components added/removed will be handled by the event handler beyond this point.
	const auto manager = this->getEntityManager();

	if(manager != nullptr)
	{
		manager->each([this](auto& e) {
			if(e.hasComponent<KinematicComponent>() == true)
			{
				this->pimpl->addBody(e);
			}

			if(e.hasComponent<BoxCollisionComponent>() == true)
			{
				this->pimpl->addBox(e);
			}

			if(e.hasComponent<CircleCollisionComponent>() == true)
			{
				this->pimpl->addCircle(e);
			}

			if(e.hasComponent<EdgeCollisionComponent>() == true)
			{
				this->pimpl->addEdge(e);
			}
		});
	}
}

void PhysicsSystem::frame(std::chrono::microseconds x)
{
	for(auto body = this->pimpl->world.GetBodyList(); body != nullptr; body = body->GetNext())
	{
		auto entity = reinterpret_cast<Entity*>(body->GetUserData());

		if(entity->hasComponent<KinematicComponent>() == true)
		{
			this->pimpl->configureBody2D(body, entity->getComponent<KinematicComponent>());
		}

		if(entity->hasComponent<BoxCollisionComponent>() == true)
		{
			this->pimpl->configureBox2D(body->GetFixtureList(), entity->getComponent<BoxCollisionComponent>());
		}

		if(entity->hasComponent<CircleCollisionComponent>() == true)
		{
			this->pimpl->configureCircle2D(body->GetFixtureList(), entity->getComponent<CircleCollisionComponent>());
		}

		if(entity->hasComponent<EdgeCollisionComponent>() == true)
		{
			this->pimpl->configureEdge2D(body->GetFixtureList(), entity->getComponent<EdgeCollisionComponent>());
		}

		if(entity->hasComponent<TransformComponent>() == true)
		{
			this->pimpl->configureBody2D(body, entity->getComponent<TransformComponent>());
		}
	}

	const auto seconds = std::chrono::duration_cast<age::core::seconds>(x);
	this->pimpl->world.Step(static_cast<float32>(seconds.count()), 6, 2);

	for(auto body = this->pimpl->world.GetBodyList(); body != nullptr; body = body->GetNext())
	{
		auto entity = reinterpret_cast<Entity*>(body->GetUserData());

		if(entity->hasComponent<KinematicComponent>() == true)
		{
			this->pimpl->configureBodyAge(body, entity->getComponent<KinematicComponent>());
		}

		if(entity->hasComponent<TransformComponent>() == true)
		{
			this->pimpl->configureBodyAge(body, entity->getComponent<TransformComponent>());
		}

		if(entity->hasComponent<KinematicComponent>() == true && entity->hasComponent<TransformComponent>() == true)
		{
			auto& k = entity->getComponent<KinematicComponent>();
			auto& t = entity->getComponent<TransformComponent>();

			if(k.CalculateHeading == true)
			{
				t.Rotation = VectorAngle({k.LinearVelocity.X, -k.LinearVelocity.Y});
			}
		}
	}
}
