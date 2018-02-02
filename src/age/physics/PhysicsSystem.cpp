#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/core/Timer.h>
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
	const auto entities = manager->getEntities();
	const auto seconds = std::chrono::duration_cast<age::core::seconds>(x);

	manager->each<TransformComponent, KinematicComponent>([s = seconds.count(), &entities, manager](Entity e, TransformComponent& t, KinematicComponent& k) {

		auto pos = t.getPosition();
		pos += k.getVelocity() * s;

		auto rot = t.getRotation();
		rot += k.getAngularVelocity() * s;

		if(e.hasComponent<BoxCollisionComponent>() == true)
		{
			auto hasCollision = false;
			manager->each<TransformComponent, BoxCollisionComponent>([&hasCollision, &e, &t](Entity ex, TransformComponent& tx, BoxCollisionComponent& bx) {
				if(e != ex)
				{
					const auto& b = e.getComponent<BoxCollisionComponent>();
					const auto p = t.getPosition();
					const auto s = b.getSize();
					const auto c = b.getCenter();

					const auto px = tx.getPosition();
					const auto sx = bx.getSize();
					const auto cx = bx.getCenter();

					// Calculate collision.

				}
			});

			// Collision detection occured.
			// Update position accordingly.
		}

		t.setPosition(pos);
		t.setRotation(rot);
	});
}
