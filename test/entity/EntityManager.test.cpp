#include <age/entity/EntityManager.h>
#include <gtest/gtest.h>

#include <entt/entt.hpp>

using namespace age::entity;

struct Position
{
	double x{};
	double y{};
};

struct Velocity
{
	double x{};
	double y{};
};

struct Drawable
{
	std::string draw{};
};

TEST(EntityManager, create)
{
	EntityManager manager;

	const auto entityCount = 5;

	for(auto i = 0; i < entityCount; i++)
	{
		const auto entity = manager.create();
		EXPECT_TRUE(entity.valid());
		EXPECT_EQ(entity.getID(), i);
	}
}

TEST(EntityManager, destroy)
{
	EntityManager manager;

	const auto entity = manager.create();
	EXPECT_TRUE(entity.valid());

	manager.destroy(entity);
	EXPECT_FALSE(entity.valid());

	const auto entity2 = manager.create();
	EXPECT_TRUE(entity2.valid());

	entity2.destroy();
	EXPECT_FALSE(entity2.valid());
}

TEST(EntityManager, recreate)
{
	EntityManager manager;

	const auto entity0 = manager.create();
	EXPECT_TRUE(entity0.valid());

	const auto entity1 = manager.create();
	EXPECT_TRUE(entity1.valid());

	const auto entity2 = manager.create();
	EXPECT_TRUE(entity2.valid());

	manager.destroy(entity1);
	EXPECT_FALSE(entity1.valid());

	const auto entity3 = manager.create();
	EXPECT_TRUE(entity3.valid());
	EXPECT_EQ(entity3.getID(), entity1.getID());

	// Verify that new entities constructed after a destroyed entity
	// do not yield ids that are the same as that destroyed entity
	// after the first entity to replace it.
	const auto entity4 = manager.create();
	EXPECT_TRUE(entity4.valid());
	EXPECT_NE(entity4, entity3);
}

TEST(EntityManager, addComponent)
{
	EntityManager manager;

	auto entity = manager.create();
	entity.addComponent<Position>();
	EXPECT_TRUE(entity.hasComponent<Position>());
	EXPECT_FALSE(entity.hasComponent<Velocity>());
}

TEST(EntityManager, hasComponent)
{
	EntityManager manager;

	auto entity = manager.create();
	EXPECT_FALSE(entity.hasComponent<Position>());
	EXPECT_FALSE(entity.hasComponent<Velocity>());
	EXPECT_FALSE(entity.hasComponent<Drawable>());
}

TEST(EntityManager, removeComponent)
{
	EntityManager manager;

	auto entity = manager.create();
	entity.addComponent<Position>();
	EXPECT_TRUE(entity.hasComponent<Position>());

	entity.removeComponent<Position>();
	EXPECT_FALSE(entity.hasComponent<Position>());
}

TEST(EntityManager, each)
{
	EntityManager manager;

	const auto maxEntity = 5;

	for(auto i = 0; i < maxEntity; i++)
	{
		auto e = manager.create();
		e.addComponent<Position>();
		e.addComponent<Velocity>();
	}

	auto entityCount = 0;
	manager.each<Position>([&entityCount](Entity& e, Position&) {
		EXPECT_TRUE(e.hasComponent<Position>());
		entityCount++;
	});

	EXPECT_EQ(entityCount, maxEntity);

	entityCount = 0;
	manager.each<Velocity>([&entityCount](Entity& e, Velocity&) {
		EXPECT_TRUE(e.hasComponent<Velocity>());
		entityCount++;
	});

	EXPECT_EQ(entityCount, maxEntity);

	entityCount = 0;
	manager.each<Position, Velocity>([&entityCount](Entity& e, Position&, Velocity&) {
		EXPECT_TRUE(e.hasComponent<Position>());
		EXPECT_TRUE(e.hasComponent<Velocity>());
		entityCount++;
	});

	EXPECT_EQ(entityCount, maxEntity);

	entityCount = 0;
	manager.each<Position, Velocity, Drawable>([&entityCount](Entity&, Position&, Velocity&, Drawable&) {
		ADD_FAILURE() << "No entities should exist with Position, Velocity, and Drawable components.";
		entityCount++;
	});

	EXPECT_EQ(entityCount, 0);
}
