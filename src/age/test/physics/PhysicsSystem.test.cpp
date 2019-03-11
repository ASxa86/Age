#include <gtest/gtest.h>

#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/physics/Box2D/Box2D.h>
#include <age/physics/PhysicsSystem.h>

TEST(PhysicsSystem, ComponentPool)
{
	b2World world{{0.0, 0.0}};
	age::entity::ComponentPool<b2Body*> pool;

	{
		b2BodyDef def;
		pool.construct(0, world.CreateBody(&def));
	}

	{
		b2BodyDef def;
		pool.construct(1, world.CreateBody(&def));
	}

	EXPECT_TRUE(pool[0]->GetWorld() != nullptr);
	EXPECT_TRUE(pool[1]->GetWorld() != nullptr);
}

TEST(PhysicsSystem, EntityManager)
{
	age::entity::EntityManager manager;

	b2World world{{0.0, 0.0}};

	b2BodyDef def1;
	auto entity1 = manager.create();
	entity1.addComponent<b2Body*>(world.CreateBody(&def1));

	b2BodyDef def2;
	auto entity2 = manager.create();
	entity2.addComponent<b2Body*>(world.CreateBody(&def2));

	EXPECT_TRUE(entity1.getComponent<b2Body*>()->GetWorld() != nullptr);
	EXPECT_TRUE(entity2.getComponent<b2Body*>()->GetWorld() != nullptr);
}
