#include <age/physics/PhysicsSystem.h>
#include <age/physics/KinematicComponent.h>
#include <age/core/Entity.h>
#include <age/core/PimplImpl.h>
#include <age/math/TransformComponent.h>
#include <age/core/Timer.h>

#include <Box2D/Dynamics/b2World.h>

using namespace age::core;
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

	const auto entities = this->getEntities();

	for(const auto& entity : entities)
	{
		const auto kinematic = entity->getChild<KinematicComponent>();
		const auto transform = entity->getChild<TransformComponent>();

		if(kinematic != nullptr && transform != nullptr)
		{
			transform->setPosition(kinematic->getPosition());
			transform->setRotation(kinematic->getRotation());
		}
	}
}
