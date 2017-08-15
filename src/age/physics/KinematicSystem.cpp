#include <age/physics/KinematicSystem.h>
#include <age/physics/KinematicComponent.h>
#include <age/core/Entity.h>
#include <age/core/PimplImpl.h>
#include <age/math/TransformComponent.h>
#include <age/core/Timer.h>

#include <Box2D/Dynamics/b2World.h>

using namespace age::core;
using namespace age::math;
using namespace age::physics;

class KinematicSystem::Impl
{
public:
	Impl() :
		world({0.0f, -9.8f})
	{
	}

	b2World world;
};

KinematicSystem::KinematicSystem() : FixedSystem()
{
}

KinematicSystem::~KinematicSystem()
{
}

void KinematicSystem::frame(std::chrono::microseconds x)
{
	const auto seconds = std::chrono::duration_cast<age::core::seconds>(x);
	this->pimpl->world.Step(static_cast<float32>(seconds.count()), 8, 3);

	const auto entities = this->getEntities();

	for(const auto& entity : entities)
	{
		const auto kinematic = entity->getChild<KinematicComponent>();
		const auto transform = entity->getChild<TransformComponent>();

		if(kinematic != nullptr && transform != nullptr)
		{
			//const auto dt = std::chrono::duration_cast<age::core::seconds>(x).count();

			//const auto v = kinematic->getVelocity();
			//auto pos = transform->getPosition();
			//pos += v * dt;
			//transform->setPosition(pos);

			//const auto av = kinematic->getAngularVelocity();
			//auto rot = transform->getRotation();
			//rot += av * dt;
			//transform->setRotation(rot);

			transform->setPosition(kinematic->getPosition());
			transform->setRotation(kinematic->getRotation());
		}
	}
}

b2World& KinematicSystem::getPhysicsEngine()
{
	return this->pimpl->world;
}
