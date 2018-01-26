#ifdef WIN32
// Setting an int as void* for UserData within b2body
#pragma warning(disable : 4311 4312 4302)
#endif

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/core/Timer.h>
#include <age/entity/EntityEvent.h>
#include <age/entity/EntityManager.h>
#include <age/math/TransformComponent.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>

using namespace age::core;
using namespace age::entity;
using namespace age::math;
using namespace age::physics;

class PhysicsSystem::Impl
{
public:
	Impl() : world{{0.0f, 0.0f}}
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

void PhysicsSystem::initialize()
{
	const auto manager = this->getEntityManager();

	const auto addBody = [this](Entity e, const TransformComponent& t, const KinematicComponent& k) {
		b2BodyDef def;

		switch(k.getBodyType())
		{
			case KinematicComponent::BodyType::Kinematic:
				def.type = b2BodyType::b2_kinematicBody;
				break;

			case KinematicComponent::BodyType::Dynamic:
				def.type = b2BodyType::b2_dynamicBody;
				break;

			case KinematicComponent::BodyType::Static:
			default:
				def.type = b2BodyType::b2_staticBody;
				break;
		}

		def.position = Impl::FromVector(t.getPosition());
		def.angle = static_cast<float32>(t.getRotation());
		def.linearVelocity = Impl::FromVector(k.getVelocity());
		def.angularVelocity = static_cast<float32>(k.getAngularVelocity());
		def.active = true;
		def.userData = reinterpret_cast<void*>(e.getID());
		auto body = this->pimpl->world.CreateBody(&def);

		if(e.hasComponent<BoxCollisionComponent>() == true)
		{
			auto& b = e.getComponent<BoxCollisionComponent>();

			b2PolygonShape shape;
			shape.SetAsBox(static_cast<float32>(b.getSize().getX()), static_cast<float32>(b.getSize().getY()));

			b2FixtureDef fdef;
			fdef.shape = &shape;
			fdef.density = 1.0;
		
			body->CreateFixture(&fdef);
			body->ResetMassData();
		}
	};

	// Process any entities that are already configured to work with this system.
	manager->each<TransformComponent, KinematicComponent>(addBody);

	// Handle any entities that become valid for this system.
	EventQueue::Instance().addEventHandler(
		[this, addBody](auto x) {
			auto evt = dynamic_cast<EntityEvent*>(x);

			if(evt != nullptr)
			{
				switch(evt->getType())
				{
					case EntityEvent::Type::ComponentAdded:
					{
						auto entity = evt->getEntity();

						const auto t = evt->getComponent<TransformComponent>();
						const auto k = evt->getComponent<KinematicComponent>();
						const auto physicsComponentAdded = t != nullptr || k != nullptr;

						// Only construct a b2body if a physics component was added AND all required components exist.
						// i.e. TransformComponent gets added but no KinematicComponent means nothing happens.
						// i.e. KinematicComponent gets added but no TransformComponent means nothing happens.
						// i.e. TransformComponent gets added and KinematicComponent exists means new b2body.
						// i.e. KinematicComponent gets added and TransformComponent exists means new b2body.
						if(physicsComponentAdded == true && entity.hasComponent<TransformComponent>() == true
						   && entity.hasComponent<KinematicComponent>() == true)
						{
							const auto transform = entity.getComponent<TransformComponent>();
							const auto kinematic = entity.getComponent<KinematicComponent>();
							addBody(entity, transform, kinematic);
						}
					}
					break;

					case EntityEvent::Type::ComponentRemoved:
					{
						const auto kinematic = evt->getComponent<KinematicComponent>();

						if(kinematic != nullptr)
						{
							const auto id = evt->getEntity().getID();

							auto body = this->pimpl->world.GetBodyList();

							while(body != nullptr)
							{
								if(id == reinterpret_cast<int>(body->GetUserData()))
								{
									this->pimpl->world.DestroyBody(body);
									break;
								}

								body = body->GetNext();
							}
						}
					}
					break;

					case EntityEvent::Type::EntityRemoved:
					{
						const auto id = evt->getEntity().getID();

						auto body = this->pimpl->world.GetBodyList();

						while(body != nullptr)
						{
							if(id == reinterpret_cast<int>(body->GetUserData()))
							{
								this->pimpl->world.DestroyBody(body);
								break;
							}

							body = body->GetNext();
						}
					}
				}
			}
		},
		this);
}

void PhysicsSystem::frame(std::chrono::microseconds x)
{
	const auto seconds = std::chrono::duration_cast<age::core::seconds>(x);

	const auto manager = this->getEntityManager();
	const auto entities = manager->getEntities();

	// Update box2d bodies with latest state.
	auto body = this->pimpl->world.GetBodyList();

	while(body != nullptr)
	{
		const auto id = reinterpret_cast<int>(body->GetUserData());
		auto entity = entities[id];

		auto& transform = entity.getComponent<TransformComponent>();
		body->SetTransform(Impl::FromVector(transform.getPosition()), static_cast<float32>(transform.getRotation()));

		auto& kinematic = entity.getComponent<KinematicComponent>();
		body->SetLinearVelocity(Impl::FromVector(kinematic.getVelocity()));
		body->SetAngularVelocity(static_cast<float32>(kinematic.getAngularVelocity()));

		body = body->GetNext();
	}

	this->pimpl->world.Step(static_cast<float32>(seconds.count()), 8, 3);

	// Update components with processed physics state.
	body = this->pimpl->world.GetBodyList();

	while(body != nullptr)
	{
		const auto id = reinterpret_cast<int>(body->GetUserData());
		auto entity = entities[id];

		auto& transform = entity.getComponent<TransformComponent>();
		transform.setPosition(Impl::ToVector(body->GetPosition()));
		transform.setRotation(body->GetAngle());

		auto& kinematic = entity.getComponent<KinematicComponent>();
		kinematic.setVelocity(Impl::ToVector(body->GetLinearVelocity()));
		kinematic.setAngularVelocity(body->GetAngularVelocity());

		body = body->GetNext();
	}
}
