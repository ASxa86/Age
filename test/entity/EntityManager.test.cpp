#include <age/entity/EntityManager.h>
#include <gtest/gtest.h>

using namespace age::entity;

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
