#include <age/math/Vector.h>
#include <gtest/gtest.h>

using namespace age::math;

TEST(Vector, Constructor)
{
	{
		Vector v;
		EXPECT_DOUBLE_EQ(v.x(), 0.0);
		EXPECT_DOUBLE_EQ(v.y(), 0.0);
	}

	{
		Vector v(-1.0, 1.0);
		EXPECT_DOUBLE_EQ(v.x(), -1.0);
		EXPECT_DOUBLE_EQ(v.y(), 1.0);
	}
}

TEST(Vector, Copy)
{
	Vector v(-1.0, 1.0);
	Vector v1(v);
	Vector v2 = v;

	EXPECT_DOUBLE_EQ(v.x(), v1.x());
	EXPECT_DOUBLE_EQ(v.y(), v1.y());

	EXPECT_DOUBLE_EQ(v.x(), v2.x());
	EXPECT_DOUBLE_EQ(v.y(), v2.y());
}

TEST(Vector, Reference)
{
	Vector v;
	v.x() = -1.0;
	v.y() = 1.0;

	EXPECT_DOUBLE_EQ(v.x(), -1.0);
	EXPECT_DOUBLE_EQ(v.y(), 1.0);
}

TEST(Vector, Equals)
{
	Vector v;

	EXPECT_EQ(v, Vector());

	v.x() = 1;
	v.y() = 1;
	EXPECT_EQ(v, Vector(1, 1));

	v.x() = -1;
	v.y() = -1;
	EXPECT_EQ(v, Vector(-1, -1));
}

TEST(Vector, LessThan)
{
	Vector v;
	EXPECT_LT(v, Vector(1, 1));
}

TEST(Vector, GreaterThan)
{
	Vector v;
	EXPECT_GT(v, Vector(-1, -1));
}

TEST(Vector, OperatorPlus)
{
	Vector v1{0.0, 0.0};
	Vector v2{1.0, 0.0};
	Vector v3{0.0, 1.0};
	Vector v4{1.0, 1.0};

	EXPECT_EQ(v1, v1 + v1);
	EXPECT_EQ(v2, v2 + v1);
	EXPECT_EQ(v3, v3 + v1);
	EXPECT_EQ(v4, v4 + v1);

	const auto v5 = v1 + v2 + v3 + v4;
	EXPECT_EQ(Vector(2.0, 2.0), v5);
}

TEST(Vector, OperatorMinus)
{
	Vector v1{0.0, 0.0};
	Vector v2{1.0, 0.0};
	Vector v3{0.0, 1.0};
	Vector v4{1.0, 1.0};

	EXPECT_EQ(v1, v1 - v1);
	EXPECT_EQ(v2, v2 - v1);
	EXPECT_EQ(v3, v3 - v1);
	EXPECT_EQ(v4, v4 - v1);

	const auto v5 = v1 - v2 - v3 - v4;
	EXPECT_EQ(Vector(-2.0, -2.0), v5);
}
