#include <gtest/gtest.h>

#include <age/entity/ComponentPool.h>

using namespace age::entity;

namespace
{
	struct Value
	{
		Value(bool& x) : value{x}
		{
			this->value = true;
		}

		~Value()
		{
			this->value = false;
		}

		bool& value;
	};
}

TEST(ComponentPool, Construction)
{
	EXPECT_NO_THROW(ComponentPool<int> pool);
	EXPECT_NO_THROW(ComponentPool<int> pool(0));
	EXPECT_NO_THROW(ComponentPool<int> pool(2048));
	EXPECT_NO_THROW(ComponentPool<int> pool(1000000));
}

TEST(ComponetPool, Capacity)
{
	{
		constexpr auto capacity = 0;
		ComponentPool<int> pool(capacity);
		EXPECT_EQ(pool.capacity(), capacity);
	}

	{
		constexpr auto capacity = 1;
		ComponentPool<int> pool(capacity);
		EXPECT_EQ(pool.capacity(), capacity);
	}

	{
		constexpr auto capacity = 2;
		ComponentPool<int> pool(capacity);
		EXPECT_EQ(pool.capacity(), capacity);
	}

	{
		constexpr auto capacity = 1000000;
		ComponentPool<int> pool(capacity);
		EXPECT_EQ(pool.capacity(), capacity);
	}
}

TEST(ComponentPool, Construct)
{
	ComponentPool<int> pool;
	EXPECT_NO_THROW(pool.construct(0, 0));
	EXPECT_NO_THROW(pool.construct(1, 1));
	EXPECT_NO_THROW(pool.construct(2, 2));
}

TEST(ComponentPool, Destroy)
{
	ComponentPool<int> pool;
	EXPECT_NO_THROW(pool.construct(0, 0));
	EXPECT_NO_THROW(pool.construct(1, 1));
	EXPECT_NO_THROW(pool.construct(2, 2));

	EXPECT_NO_THROW(pool.destroy(0));
	EXPECT_NO_THROW(pool.destroy(1));
	EXPECT_NO_THROW(pool.destroy(2));
}

TEST(ComponentPool, Test)
{
	ComponentPool<int> pool;
	EXPECT_NO_THROW(pool.construct(0, 0));
	EXPECT_NO_THROW(pool.construct(1, 1));
	EXPECT_NO_THROW(pool.construct(2, 2));

	EXPECT_TRUE(pool.test(0));
	EXPECT_TRUE(pool.test(1));
	EXPECT_TRUE(pool.test(2));
	EXPECT_FALSE(pool.test(3));
	EXPECT_FALSE(pool.test(pool.capacity() - 1));
}

TEST(ComponentPool, Value)
{
	ComponentPool<Value> pool;

	{
		bool valueTest{false};
		pool.construct(0, valueTest);
		EXPECT_TRUE(pool.test(0));
		EXPECT_TRUE(valueTest);
		pool.destroy(0);
		EXPECT_FALSE(valueTest);
		EXPECT_FALSE(pool.test(0));
	}

	{
		bool valueTest{false};
		pool.construct(2, valueTest);
		EXPECT_TRUE(valueTest);
		EXPECT_TRUE(pool.test(2));
		pool.destroy(2);
		EXPECT_FALSE(valueTest);
		EXPECT_FALSE(pool.test(2));
	}

	{
		bool valueTest{false};
		pool.construct(pool.capacity() - 1, valueTest);
		EXPECT_TRUE(valueTest);
		EXPECT_TRUE(pool.test(pool.capacity() - 1));
		pool.destroy(pool.capacity() - 1);
		EXPECT_FALSE(valueTest);
		EXPECT_FALSE(pool.test(pool.capacity() - 1));
	}
}
