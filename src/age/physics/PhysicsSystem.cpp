#include <Box2D/Dynamics/b2World.h>
#include <age/core/Timer.h>
#include <age/entity/EntityManager.h>
#include <age/math/TransformComponent.h>
#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>

using namespace age::core;
using namespace age::entity;
using namespace age::math;
using namespace age::physics;

/// I made this a global variable in order to construct physics components.
/// Specifically, this allows the construction of b2body objects within the constructor
/// of physics components without having to pass this object around.
static b2World PhysicsEngine({0.0f, -9.8f});

PhysicsSystem::PhysicsSystem() : FixedSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

b2World& PhysicsSystem::Engine()
{
	static b2World engine({0.0f, -9.8f});
	return engine;
}

void PhysicsSystem::frame(std::chrono::microseconds x)
{
	const auto seconds = std::chrono::duration_cast<age::core::seconds>(x);
	PhysicsSystem::Engine().Step(static_cast<float32>(seconds.count()), 8, 3);

	const auto manager = this->getEntityManager();

	manager->each<KinematicComponent, TransformComponent>([](Entity, KinematicComponent& k, TransformComponent& t) {
		t.setPosition(k.getPosition());
		t.setRotation(k.getRotation());
	});
}
