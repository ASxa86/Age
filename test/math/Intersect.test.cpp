#include <age/math/Intersect.h>

#include <age/math/BoundingBox.h>
#include <age/math/BoundingCircle.h>
#include <gtest/gtest.h>

using namespace age::math;

TEST(Intersect, BoundingBoxFalse)
{
	BoundingBox bb({0.0, 0.0}, {1.0, 1.0});
	BoundingBox left({-2.0, 0.0}, {1.0, 1.0});
	BoundingBox right({2.0, 0.0}, {1.0, 1.0});
	BoundingBox bottom({0.0, 2.0}, {1.0, 1.0});
	BoundingBox top({0.0, -2.0}, {1.0, 1.0});

	// Verify the bounding boxes don't intersect with themselves.
	EXPECT_FALSE(age::math::intersect(bb, bb));
	EXPECT_FALSE(age::math::intersect(left, left));
	EXPECT_FALSE(age::math::intersect(right, right));
	EXPECT_FALSE(age::math::intersect(bottom, bottom));
	EXPECT_FALSE(age::math::intersect(top, top));

	EXPECT_FALSE(age::math::intersect(bb, left));
	EXPECT_FALSE(age::math::intersect(bb, right));
	EXPECT_FALSE(age::math::intersect(bb, bottom));
	EXPECT_FALSE(age::math::intersect(bb, top));

	EXPECT_FALSE(age::math::intersect(left, bb));
	EXPECT_FALSE(age::math::intersect(right, bb));
	EXPECT_FALSE(age::math::intersect(bottom, bb));
	EXPECT_FALSE(age::math::intersect(top, bb));
}

TEST(Intersect, BoundingBoxEdge)
{
	BoundingBox bb({0.0, 0.0}, {1.0, 1.0});
	BoundingBox left({-1.0, 0.0}, {1.0, 1.0});
	BoundingBox right({1.0, 0.0}, {1.0, 1.0});
	BoundingBox bottom({0.0, 1.0}, {1.0, 1.0});
	BoundingBox top({0.0, -1.0}, {1.0, 1.0});

	// Verify the bounding boxes don't intersect with themselves.
	EXPECT_FALSE(age::math::intersect(bb, bb));
	EXPECT_FALSE(age::math::intersect(left, left));
	EXPECT_FALSE(age::math::intersect(right, right));
	EXPECT_FALSE(age::math::intersect(bottom, bottom));
	EXPECT_FALSE(age::math::intersect(top, top));

	EXPECT_TRUE(age::math::intersect(bb, left));
	EXPECT_TRUE(age::math::intersect(bb, right));
	EXPECT_TRUE(age::math::intersect(bb, bottom));
	EXPECT_TRUE(age::math::intersect(bb, top));

	EXPECT_TRUE(age::math::intersect(left, bb));
	EXPECT_TRUE(age::math::intersect(right, bb));
	EXPECT_TRUE(age::math::intersect(bottom, bb));
	EXPECT_TRUE(age::math::intersect(top, bb));
}

TEST(Intersect, BoundingBoxTrue)
{
	BoundingBox bb({0.0, 0.0}, {1.0, 1.0});
	BoundingBox left({-0.5, 0.0}, {1.0, 1.0});
	BoundingBox right({0.5, 0.0}, {1.0, 1.0});
	BoundingBox bottom({0.0, 0.5}, {1.0, 1.0});
	BoundingBox top({0.0, -0.5}, {1.0, 1.0});

	// Verify the bounding boxes don't intersect with themselves.
	EXPECT_FALSE(age::math::intersect(bb, bb));
	EXPECT_FALSE(age::math::intersect(left, left));
	EXPECT_FALSE(age::math::intersect(right, right));
	EXPECT_FALSE(age::math::intersect(bottom, bottom));
	EXPECT_FALSE(age::math::intersect(top, top));

	EXPECT_TRUE(age::math::intersect(bb, left));
	EXPECT_TRUE(age::math::intersect(bb, right));
	EXPECT_TRUE(age::math::intersect(bb, bottom));
	EXPECT_TRUE(age::math::intersect(bb, top));

	EXPECT_TRUE(age::math::intersect(left, bb));
	EXPECT_TRUE(age::math::intersect(right, bb));
	EXPECT_TRUE(age::math::intersect(bottom, bb));
	EXPECT_TRUE(age::math::intersect(top, bb));
}

TEST(Intersect, BoundingCircleFalse)
{
	BoundingCircle bc({0.0, 0.0}, 0.5);
	BoundingCircle left({-2.0, 0.0}, 0.5);
	BoundingCircle right({2.0, 0.0}, 0.5);
	BoundingCircle bottom({0.0, 2.0}, 0.5);
	BoundingCircle top({0.0, -2.0}, 0.5);

	EXPECT_FALSE(age::math::intersect(bc, bc));
	EXPECT_FALSE(age::math::intersect(left, left));
	EXPECT_FALSE(age::math::intersect(right, right));
	EXPECT_FALSE(age::math::intersect(bottom, bottom));
	EXPECT_FALSE(age::math::intersect(top, top));

	EXPECT_FALSE(age::math::intersect(bc, left));
	EXPECT_FALSE(age::math::intersect(bc, right));
	EXPECT_FALSE(age::math::intersect(bc, bottom));
	EXPECT_FALSE(age::math::intersect(bc, top));

	EXPECT_FALSE(age::math::intersect(left, bc));
	EXPECT_FALSE(age::math::intersect(right, bc));
	EXPECT_FALSE(age::math::intersect(bottom, bc));
	EXPECT_FALSE(age::math::intersect(top, bc));
}

TEST(Intersect, BoundingCircleEdge)
{
	BoundingCircle bc({0.0, 0.0}, 0.5);
	BoundingCircle left({-1.0, 0.0}, 0.5);
	BoundingCircle right({1.0, 0.0}, 0.5);
	BoundingCircle bottom({0.0, 1.0}, 0.5);
	BoundingCircle top({0.0, -1.0}, 0.5);

	EXPECT_FALSE(age::math::intersect(bc, bc));
	EXPECT_FALSE(age::math::intersect(left, left));
	EXPECT_FALSE(age::math::intersect(right, right));
	EXPECT_FALSE(age::math::intersect(bottom, bottom));
	EXPECT_FALSE(age::math::intersect(top, top));

	EXPECT_TRUE(age::math::intersect(bc, left));
	EXPECT_TRUE(age::math::intersect(bc, right));
	EXPECT_TRUE(age::math::intersect(bc, bottom));
	EXPECT_TRUE(age::math::intersect(bc, top));

	EXPECT_TRUE(age::math::intersect(left, bc));
	EXPECT_TRUE(age::math::intersect(right, bc));
	EXPECT_TRUE(age::math::intersect(bottom, bc));
	EXPECT_TRUE(age::math::intersect(top, bc));
}

TEST(Intersect, BoundingCircleTrue)
{
	BoundingCircle bc({0.0, 0.0}, 0.5);
	BoundingCircle left({-0.5, 0.0}, 0.5);
	BoundingCircle right({0.5, 0.0}, 0.5);
	BoundingCircle bottom({0.0, 0.5}, 0.5);
	BoundingCircle top({0.0, -0.5}, 0.5);

	EXPECT_FALSE(age::math::intersect(bc, bc));
	EXPECT_FALSE(age::math::intersect(left, left));
	EXPECT_FALSE(age::math::intersect(right, right));
	EXPECT_FALSE(age::math::intersect(bottom, bottom));
	EXPECT_FALSE(age::math::intersect(top, top));

	EXPECT_TRUE(age::math::intersect(bc, left));
	EXPECT_TRUE(age::math::intersect(bc, right));
	EXPECT_TRUE(age::math::intersect(bc, bottom));
	EXPECT_TRUE(age::math::intersect(bc, top));

	EXPECT_TRUE(age::math::intersect(left, bc));
	EXPECT_TRUE(age::math::intersect(right, bc));
	EXPECT_TRUE(age::math::intersect(bottom, bc));
	EXPECT_TRUE(age::math::intersect(top, bc));
}

TEST(Intersect, BoundingBoxBoundingCircleFalse)
{
	BoundingBox bb({0.0, 0.0}, {1.0, 1.0});
	BoundingCircle left({-2.0, 0.0}, 0.5);
	BoundingCircle right({2.0, 0.0}, 0.5);
	BoundingCircle bottom({0.0, 2.0}, 0.5);
	BoundingCircle top({0.0, -2.0}, 0.5);

	EXPECT_FALSE(age::math::intersect(bb, bb));
	EXPECT_FALSE(age::math::intersect(left, left));
	EXPECT_FALSE(age::math::intersect(right, right));
	EXPECT_FALSE(age::math::intersect(bottom, bottom));
	EXPECT_FALSE(age::math::intersect(top, top));

	EXPECT_FALSE(age::math::intersect(bb, left));
	EXPECT_FALSE(age::math::intersect(bb, right));
	EXPECT_FALSE(age::math::intersect(bb, bottom));
	EXPECT_FALSE(age::math::intersect(bb, top));
}

TEST(Intersect, BoundingBoxBoundingCircleEdge)
{
	BoundingBox bb({0.0, 0.0}, {1.0, 1.0});
	BoundingCircle left({-1.0, 0.0}, 0.5);
	BoundingCircle right({1.0, 0.0}, 0.5);
	BoundingCircle bottom({0.0, 1.0}, 0.5);
	BoundingCircle top({0.0, -1.0}, 0.5);

	EXPECT_FALSE(age::math::intersect(bb, bb));
	EXPECT_FALSE(age::math::intersect(left, left));
	EXPECT_FALSE(age::math::intersect(right, right));
	EXPECT_FALSE(age::math::intersect(bottom, bottom));
	EXPECT_FALSE(age::math::intersect(top, top));

	EXPECT_TRUE(age::math::intersect(bb, left));
	EXPECT_TRUE(age::math::intersect(bb, right));
	EXPECT_TRUE(age::math::intersect(bb, bottom));
	EXPECT_TRUE(age::math::intersect(bb, top));

	BoundingCircle topLeft{{-0.65, -0.65}, 0.5};
	BoundingCircle topRight{{0.65, -0.65}, 0.5};
	BoundingCircle bottomLeft{{-0.65, 0.65}, 0.5};
	BoundingCircle bottomRight{{0.65, 0.65}, 0.5};

	EXPECT_TRUE(age::math::intersect(bb, topLeft));
	EXPECT_TRUE(age::math::intersect(bb, topRight));
	EXPECT_TRUE(age::math::intersect(bb, bottomLeft));
	EXPECT_TRUE(age::math::intersect(bb, bottomRight));
}
