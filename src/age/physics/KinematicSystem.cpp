#include <age/physics/KinematicSystem.h>
#include <age/physics/KinematicComponent.h>
#include <age/core/Entity.h>
#include <age/core/TransformComponent.h>
#include <age/core/Timer.h>

using namespace age::core;
using namespace age::physics;

KinematicSystem::KinematicSystem() : FixedSystem()
{
}

KinematicSystem::~KinematicSystem()
{
}

void KinematicSystem::frame(std::chrono::microseconds x)
{
	const auto entities = this->getEntities();

	for(const auto& entity : entities)
	{
		const auto kinematic = entity->getChild<KinematicComponent>();
		const auto transform = entity->getChild<TransformComponent>();

		if(kinematic != nullptr && transform != nullptr)
		{
			const auto dt = std::chrono::duration_cast<age::core::seconds>(x).count();

			const auto v = kinematic->getVelocity();
			auto pos = transform->getPosition();
			pos[0] += v[0] * dt;
			pos[1] += v[1] * dt;
			transform->setPosition(pos);

			const auto av = kinematic->getAngularVelocity();
			auto rot = transform->getRotation();
			rot += av * dt;
			transform->setRotation(rot);
		}
	}
}
