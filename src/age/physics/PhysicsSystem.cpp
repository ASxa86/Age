#include <age/physics/PhysicsSystem.h>
#include <age/physics/KinematicComponent.h>
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

void PhysicsSystem::frame(const std::vector<age::entity::Entity>& entities, std::chrono::microseconds x)
{
	const auto seconds = std::chrono::duration_cast<age::core::seconds>(x);
	PhysicsSystem::Engine().Step(static_cast<float32>(seconds.count()), 8, 3);

	for(auto entity : entities)
	{
		if(entity.valid() == true && entity.hasComponent<KinematicComponent>() == true && entity.hasComponent<TransformComponent>() == true)
		{
			auto& kinematic = entity.getComponent<KinematicComponent>();
			auto& transform = entity.getComponent<TransformComponent>();

			transform.setPosition(kinematic.getPosition());
			transform.setRotation(kinematic.getRotation());
		}
	}
}
