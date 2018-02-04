#include <age/physics/PhysicsSystem.h>

#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/core/Timer.h>
#include <age/entity/EntityManager.h>
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
						const auto p = t.getPosition();
						const auto s = b.getSize();
						const auto c = b.getCenter();

						const auto px = tx.getPosition();
						const auto sx = bx.getSize();
						const auto cx = bx.getCenter();

						// Calculate collision.

						const auto left = p.getX() - (s.getX() * 0.5);
						const auto right = p.getX() + (s.getX() * 0.5);
						const auto top = p.getY() - (s.getY() * 0.5);
						const auto bottom = p.getY() + (s.getY() * 0.5);

						const auto xleft = px.getX() - (sx.getX() * 0.5);
						const auto xright = px.getX() + (sx.getX() * 0.5);
						const auto xtop = px.getY() - (sx.getY() * 0.5);
						const auto xbottom = px.getY() + (sx.getY() * 0.5);

						const auto leftIsBetweenLeftAndRight = left >= xleft && left <= xright;
						const auto rightIsBetweenLeftAndRight = right <= xright && right >= xleft;
						const auto topIsBetweenTopAndBottom = top >= xtop && top <= xbottom;
						const auto bottomIsBetweenTopAndBotton = bottom <= xbottom && bottom >= xtop;

						// Test left and top
						if(leftIsBetweenLeftAndRight == true && topIsBetweenTopAndBottom == true)
						{
							hasCollision = true;
						}

						// Test left and bottom
						else if(leftIsBetweenLeftAndRight == true && bottomIsBetweenTopAndBotton == true)
						{
							hasCollision = true;
						}

						// Test right and top
						else if(rightIsBetweenLeftAndRight == true && topIsBetweenTopAndBottom == true)
						{
							hasCollision = true;
						}

						// Test right and bottom
						else if(rightIsBetweenLeftAndRight == true && bottomIsBetweenTopAndBotton == true)
						{
							hasCollision = true;
						}

						if(hasCollision == true)
						{
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
