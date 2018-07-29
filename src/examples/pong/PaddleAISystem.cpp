#include <examples/pong/PaddleAISystem.h>

#include <Box2D/Box2D.h>
#include <age/entity/EntityManager.h>
#include <age/physics/BodyComponent.h>
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

	manager->each<PaddleAIComponent, BodyComponent>([](Entity&, PaddleAIComponent& p, BodyComponent& b) {
		const auto ball = p.getBall();

		if(ball != nullptr)
		{
			auto& bc = ball->getComponent<BodyComponent>();
			const auto posBall = bc.body->GetPosition();
			const auto posPaddle = b.body->GetPosition();
			auto aabb = b.body->GetFixtureList()->GetAABB(0);

			b.body->SetLinearVelocity({0.0f, 0.0f});

			if(posBall.y > aabb.upperBound.y)
			{
				b.body->SetLinearVelocity({0.0f, 30.0f});
			}
			else if(posBall.y < aabb.lowerBound.y)
			{
				b.body->SetLinearVelocity({0.0f, -30.0f});
			}
		}
	});
}
