#include <PaddleAISystem.h>

#include <PaddleAIComponent.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/TransformComponent.h>
#include <azule/physics/BoxCollisionComponent.h>
#include <azule/physics/KinematicComponent.h>

using namespace azule::entity;
using namespace azule::physics;
using namespace azule::pong;

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
