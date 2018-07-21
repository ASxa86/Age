#include <age/core/EventQueue.h>
#include <age/entity/EntityEvent.h>
#include <age/entity/EntityManager.h>
#include <gtest/gtest.h>

using namespace age::core;
using namespace age::entity;

struct Value
{
	int v{};
};

TEST(EntityEvent, EntityAdded)
{
	auto eventReceived = false;
	auto connection = EventQueue::Instance().addEventHandler([&eventReceived](auto event) {
		const auto entityEvent = dynamic_cast<EntityEvent*>(event);
		ASSERT_TRUE(entityEvent != nullptr);

		EXPECT_EQ(entityEvent->getType(), EntityEvent::Type::EntityAdded);
		EXPECT_TRUE(entityEvent->getComponent<Value>() == nullptr);
		EXPECT_FALSE(entityEvent->getEntity().hasComponent<Value>());
		eventReceived = true;
	});

	EntityManager manager;
	const auto e = manager.create();

	EXPECT_TRUE(eventReceived);
	connection.disconnect();
}

TEST(EntityEvent, EntityRemoved)
{
	EntityManager manager;
	const auto e = manager.create();

	auto eventReceived = false;
	auto connection = EventQueue::Instance().addEventHandler([&eventReceived](auto event) {
		const auto entityEvent = dynamic_cast<EntityEvent*>(event);
		ASSERT_TRUE(entityEvent != nullptr);

		EXPECT_EQ(entityEvent->getType(), EntityEvent::Type::EntityRemoved);
		EXPECT_TRUE(entityEvent->getComponent<Value>() == nullptr);
		EXPECT_FALSE(entityEvent->getEntity().hasComponent<Value>());
		eventReceived = true;
	});

	e.destroy();
	EXPECT_TRUE(eventReceived);

	eventReceived = false;

	e.destroy();
	EXPECT_FALSE(eventReceived);

	connection.disconnect();
}

TEST(EntityEvent, ComponentAdded)
{
	EntityManager manager;
	auto e = manager.create();

	auto eventReceived = false;
	auto connection = EventQueue::Instance().addEventHandler([&eventReceived](auto event) {
		const auto entityEvent = dynamic_cast<EntityEvent*>(event);
		ASSERT_TRUE(entityEvent != nullptr);

		EXPECT_EQ(entityEvent->getType(), EntityEvent::Type::ComponentAdded);
		EXPECT_TRUE(entityEvent->getComponent<Value>() != nullptr);
		EXPECT_TRUE(entityEvent->getEntity().hasComponent<Value>());
		eventReceived = true;
	});

	e.addComponent<Value>();
	EXPECT_TRUE(eventReceived);

	eventReceived = false;

	e.addComponent<Value>();
	EXPECT_FALSE(eventReceived);

	connection.disconnect();
}

TEST(EntityEvent, ComponentRemoved)
{
	EntityManager manager;
	auto e = manager.create();
	e.addComponent<Value>();

	auto eventReceived = false;
	auto connection = EventQueue::Instance().addEventHandler([&eventReceived](auto event) {
		const auto entityEvent = dynamic_cast<EntityEvent*>(event);
		ASSERT_TRUE(entityEvent != nullptr);

		EXPECT_EQ(entityEvent->getType(), EntityEvent::Type::ComponentRemoved);
		EXPECT_TRUE(entityEvent->getComponent<Value>() != nullptr);
		EXPECT_TRUE(entityEvent->getEntity().hasComponent<Value>());
		eventReceived = true;
	});

	e.removeComponent<Value>();
	EXPECT_TRUE(eventReceived);
	EXPECT_FALSE(e.hasComponent<Value>());

	eventReceived = false;

	e.removeComponent<Value>();
	EXPECT_FALSE(eventReceived);
	EXPECT_FALSE(e.hasComponent<Value>());

	connection.disconnect();
}
