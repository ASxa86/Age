#include <gtest/gtest.h>

#include <age/entity/ComponentPool.h>

using namespace age::entity;

namespace
{
	bool reference{false};
	struct Value
	{
		Value(bool& x = reference) : value{x}
		{
			this->value = true;
		}

		Value(Value&& x) : value{x.value}
		{
		}

		Value& operator=(Value&& x)
		{
			this->value = x.value;
			return *this;
		}

		Value(const Value&) = delete;
		Value& operator=(const Value&) = delete;

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
}
