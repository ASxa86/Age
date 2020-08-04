#include <azule/math/Functions.h>
#include <azule/math/GLM.h>
#include <gtest/gtest.h>

using namespace azule;

TEST(Functions, VectorAngle)
{
	EXPECT_DOUBLE_EQ(VectorAngle({0.0, 0.0}), 0.0);
	EXPECT_DOUBLE_EQ(VectorAngle({1.0, 1.0}), 45.0);
	EXPECT_DOUBLE_EQ(VectorAngle({1.0, 0.0}), 90.0);
	EXPECT_DOUBLE_EQ(VectorAngle({1.0, -1.0}), 135.0);
	EXPECT_DOUBLE_EQ(VectorAngle({0.0, -1.0}), 180.0);
	EXPECT_DOUBLE_EQ(VectorAngle({-1.0, -1.0}), 225.0);
	EXPECT_DOUBLE_EQ(VectorAngle({-1.0, 0.0}), 270.0);
	EXPECT_DOUBLE_EQ(VectorAngle({-1.0, 1.0}), 315);
	EXPECT_DOUBLE_EQ(VectorAngle({0.0, 1.0}), 0.0);
}

TEST(Function, Clamp)
{
	EXPECT_DOUBLE_EQ(Clamp(0.0, 0.0, 0.0), 0.0);
	EXPECT_DOUBLE_EQ(Clamp(0.0, 0.0, 1.0), 0.0);
	EXPECT_DOUBLE_EQ(Clamp(0.0, 1.0, 0.0), 1.0);
	EXPECT_DOUBLE_EQ(Clamp(0.0, 1.0, 1.0), 1.0);

	EXPECT_DOUBLE_EQ(Clamp(-1.0, 0.0, 1.0), 0.0);
	EXPECT_DOUBLE_EQ(Clamp(2.0, 0.0, 1.0), 1.0);
}

TEST(Function, Contrain)
{
	EXPECT_DOUBLE_EQ(Constrain(0.0, 0.0, 360.0), 0.0);
	EXPECT_DOUBLE_EQ(Constrain(90.0, 0.0, 360.0), 90.0);
	EXPECT_DOUBLE_EQ(Constrain(180.0, 0.0, 360.0), 180.0);
	EXPECT_DOUBLE_EQ(Constrain(270.0, 0.0, 360.0), 270.0);
	EXPECT_DOUBLE_EQ(Constrain(360.0, 0.0, 360.0), 360.0);

	EXPECT_DOUBLE_EQ(Constrain(-90.0, 0.0, 360.0), 270.0);
	EXPECT_DOUBLE_EQ(Constrain(-180.0, 0.0, 360.0), 180.0);
	EXPECT_DOUBLE_EQ(Constrain(-270.0, 0.0, 360.0), 90.0);
	EXPECT_DOUBLE_EQ(Constrain(-360.0, 0.0, 360.0), 0.0);
}
