//#include <examples/pong/PaddleAISystem.h>
//
//#include <Box2D/Box2D.h>
//#include <age/entity/EntityManager.h>
//#include <age/entity/TransformComponent.h>
//#include <age/physics/KinematicComponent.h>
//#include <examples/pong/PaddleAIComponent.h>
//
// using namespace age::entity;
// using namespace age::physics;
// using namespace age::pong;
//
// PaddleAISystem::PaddleAISystem()
//{
//	this->addFixedFunction([this](auto x) { this->frame(x); });
//}
//
// PaddleAISystem::~PaddleAISystem()
//{
//}
//
// void PaddleAISystem::frame(std::chrono::microseconds)
//{
//	const auto manager = this->getEntityManager();
//
//	manager->each<PaddleAIComponent, KinematicComponent, TransformComponent>(
//		[](Entity&, PaddleAIComponent& p, KinematicComponent& k, TransformComponent& t) {
//			const auto ball = p.getBall();
//
//			if(ball != nullptr)
//			{
//				auto& bc = ball->getComponent<TransformComponent>();
//				const auto posBall = bc.getPosition();
//				const auto posPaddle = t.getPosition();
//
//				b.Body->SetLinearVelocity({0.0f, 0.0f});
//
//				if(posBall.y > aabb.upperBound.y)
//				{
//					b.Body->SetLinearVelocity({0.0f, 30.0f});
//				}
//				else if(posBall.y < aabb.lowerBound.y)
//				{
//					b.Body->SetLinearVelocity({0.0f, -30.0f});
//				}
//			}
//		});
//}
