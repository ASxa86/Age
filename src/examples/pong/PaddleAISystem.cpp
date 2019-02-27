#include <examples/pong/PaddleAISystem.h>

#include <Box2D/Box2D.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/KinematicComponent.h>
#include <examples/pong/PaddleAIComponent.h>

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
	const auto manager = this->getEntityManager();

	manager->each<PaddleAIComponent, KinematicComponent, BoxCollisionComponent, TransformComponent>(
		[](Entity&, PaddleAIComponent& p, KinematicComponent& k, BoxCollisionComponent& b, TransformComponent& t) {
			const auto& ball = p.getBall();

			auto& bc = ball.getComponent<TransformComponent>();

			k.LinearVelocity = {0.0, 0.0};

			const auto top = t.Position.Y - b.Height / 2.0;
			const auto bottom = t.Position.Y + b.Height / 2.0;

			if(bc.Position.Y > bottom)
			{
				k.LinearVelocity = {0.0, 30.0};
			}
			else if(bc.Position.Y < top)
			{
				k.LinearVelocity = {0.0, -30.0};
			}
		});
}
