#include <PaddleAISystem.h>

#include <PaddleAIComponent.h>
#include <age/entity/EntityDatabase.h>
#include <age/entity/TransformComponent.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/KinematicComponent.h>

using namespace age::entity;
using namespace age::physics;
using namespace age::pong;

PaddleAISystem::PaddleAISystem()
{
	this->addFixedFunction([this](auto x) { this->frame(x); });
}

PaddleAISystem::~PaddleAISystem()
{
}

void PaddleAISystem::frame(std::chrono::microseconds)
{
	const auto manager = this->getEntityDatabase();

	for(auto entity : manager->getChildren<Entity>())
	{
		auto p = entity->getChild<PaddleAIComponent>();
		auto k = entity->getChild<KinematicComponent>();
		auto b = entity->getChild<BoxCollisionComponent>();
		auto t = entity->getChild<TransformComponent>();

		if(p != nullptr && k != nullptr && b != nullptr && t != nullptr)
		{
			const auto& ball = p->getBall();

			auto bc = ball.getChild<TransformComponent>();

			k->LinearVelocity = {0.0, 0.0};

			const auto top = t->Position.Y - b->Height / 2.0;
			const auto bottom = t->Position.Y + b->Height / 2.0;

			if(bc->Position.Y > bottom)
			{
				k->LinearVelocity = {0.0, 30.0};
			}
			else if(bc->Position.Y < top)
			{
				k->LinearVelocity = {0.0, -30.0};
			}
		}
	}
}
