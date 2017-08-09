#include <age/physics/CollisionSystem.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/math/TransformComponent.h>
#include <age/core/Entity.h>

using namespace age::core;
using namespace age::math;
using namespace age::physics;

CollisionSystem::CollisionSystem() : FixedSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::frame(std::chrono::microseconds)
{
	const auto entities = this->getEntities();

	//for(const auto& entity : entities)
	//{
	//	const auto transform = entity->getChild<TransformComponent>();
	//	const auto boxCollision = entity->getChild<BoxCollisionComponent>();

	//	if(transform != nullptr && boxCollision != nullptr)
	//	{
	//		// tree->move(boxCollision)
	//		// auto boxesInRange = tree->query(boxCollision);
	//		// for each box in range
	//		{
	//			// box->intersects(boxCollision);
	//		}
	//	}
	//}

	for(size_t i = 0; i < entities.size(); i++)
	{
		for(size_t j = i + 1; j < entities.size(); j++)
		{
			auto a = entities[i]->getChild<BoxCollisionComponent>();
			auto b = entities[j]->getChild<BoxCollisionComponent>();

			const auto aCenter = a->getCenter();
			const auto aHalfSize = a->getSize() / 2.0;

			const auto bCenter = b->getCenter();
			const auto bHalfSize = b->getSize() / 2.0;

			const auto aLeft = aCenter.x() - aHalfSize.x();
			const auto aRight = aCenter.x() + aHalfSize.x();
			const auto aTop = aCenter.y() + aHalfSize.y();
			const auto aBottom = aCenter.y() - aHalfSize.y();

			const auto bLeft = bCenter.x() - bHalfSize.x();
			const auto bRight = bCenter.x() + bHalfSize.x();
			const auto bTop = bCenter.y() + bHalfSize.y();
			const auto bBottom = bCenter.y() - bHalfSize.y();

			if (bTop <= aTop && bTop >= aBottom && bLeft <= aRight && bLeft >= aLeft)
			{

			}
		}
	}
}
