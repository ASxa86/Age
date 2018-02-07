#include <age/math/BoundingBox.h>
#include <gtest/gtest.h>

using namespace age::math;

TEST(BoundingBox, Constructor)
{
	{
		BoundingBox bb;
		EXPECT_EQ(bb.getPosition(), Vector(0.0, 0.0));
		EXPECT_EQ(bb.getSize(), Vector(0.0, 0.0));
	}

	{
		const auto pos = Vector(-1.0, -1.0);
		const auto size = Vector(1.0, 1.0);
		BoundingBox bb(pos, size);
		EXPECT_EQ(bb.getPosition(), pos);
		EXPECT_EQ(bb.getSize(), size);
	}
}

TEST(BoundingBox, Left)
{
	BoundingBox bb({0.0, 0.0}, {1.0, 1.0});
	EXPECT_DOUBLE_EQ(-0.5, bb.getLeft());
}

TEST(BoundingBox, Right)
{
	BoundingBox bb({0.0, 0.0}, {1.0, 1.0});
	EXPECT_DOUBLE_EQ(0.5, bb.getRight());
}

TEST(BoundingBox, Top)
{
	BoundingBox bb({0.0, 0.0}, {1.0, 1.0});
	EXPECT_DOUBLE_EQ(-0.5, bb.getTop());
}

TEST(BoundingBox, Bottom)
{
	BoundingBox bb({0.0, 0.0}, {1.0, 1.0});
	EXPECT_DOUBLE_EQ(0.5, bb.getBottom());
}

TEST(BoundingBox, Position)
{
	BoundingBox bb;

	const auto pos = Vector(1.0, 1.0);
	bb.setPosition(pos);
	EXPECT_EQ(pos, bb.getPosition());
}

TEST(BoundingBox, Size)
{
	BoundingBox bb;

	const auto size = Vector(1.0, 1.0);
	bb.setSize(size);
	EXPECT_EQ(size, bb.getSize());
}
