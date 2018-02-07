#include <age/physics/PhysicsSystem.h>

#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/core/Timer.h>
#include <age/entity/EntityManager.h>
#include <age/math/BoundingBox.h>
#include <age/math/Intersect.h>
#include <age/math/TransformComponent.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/CollisionEvent.h>
#include <age/physics/KinematicComponent.h>

using namespace age::core;
using namespace age::entity;
using namespace age::math;
using namespace age::physics;

class PhysicsSystem::Impl
{
public:
	Impl()
	{
	}
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
}

void PhysicsSystem::frame(std::chrono::microseconds x)
{
	const auto manager = this->getEntityManager();
	const auto seconds = std::chrono::duration_cast<age::core::seconds>(x);

	manager->each<TransformComponent, KinematicComponent>([s = seconds.count(), manager](Entity e, TransformComponent& t, KinematicComponent& k) {
		auto pos = t.getPosition();
		auto rot = t.getRotation();

		t.setPosition(pos + k.getVelocity() * s);
		t.setRotation(rot + k.getAngularVelocity() * s);

		auto hasCollision = false;

		if(e.hasComponent<BoxCollisionComponent>() == true)
		{
			auto evt = std::make_unique<CollisionEvent>();
			evt->addEntity(e);

			manager->each<TransformComponent, BoxCollisionComponent>(
				[&hasCollision, &e, &t, &evt](Entity ex, TransformComponent& tx, BoxCollisionComponent& bx) {
					if(e != ex)
					{
						const auto& b = e.getComponent<BoxCollisionComponent>();

						const BoundingBox bbA{t.getPosition() + b.getCenter(), b.getSize()};
						const BoundingBox bbB{tx.getPosition() + bx.getCenter(), bx.getSize()};

						if(age::math::intersect(bbA, bbB) == true)
						{
							hasCollision = true;
							evt->addEntity(ex);
						}
					}
				});

			if(hasCollision == true)
			{
				t.setPosition(t.getPosition() - k.getVelocity() * s);
				t.setRotation(t.getRotation() - k.getAngularVelocity() * s);
				EventQueue::Instance().sendEvent(std::move(evt));
			}
		}
	});
}
