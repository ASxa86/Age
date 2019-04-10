#include <gtest/gtest.h>

#include <age/core/Properties.h>

using namespace age::core;

TEST(Properties, PropertyInt)
{
	int x = 0;

	Properties properties;
	properties.addProperty(&x, "x");
	auto property = properties.getProperty("x");
	ASSERT_TRUE(property != nullptr);
	EXPECT_EQ("0", property->getValue());

	property->setValue("1");
	EXPECT_EQ(1, x);
}

TEST(Properties, PropertyFloat)
{
	float x = 0;

	Properties properties;
	properties.addProperty(&x, "x");
	auto property = properties.getProperty("x");
	ASSERT_TRUE(property != nullptr);
	EXPECT_EQ("0", property->getValue());

	property->setValue("1");
	EXPECT_FLOAT_EQ(1, x);
}

TEST(Properties, PropertyDouble)
{
	double x = 0;

	Properties properties;
	properties.addProperty(&x, "x");
	auto property = properties.getProperty("x");
	ASSERT_TRUE(property != nullptr);
	EXPECT_EQ("0", property->getValue());

	property->setValue("1");
	EXPECT_DOUBLE_EQ(1, x);
}

TEST(Properties, GetProperties)
{
	int i{};
	float f{};
	double d{};

	Properties properties;
	properties.addProperty(&i, "i");
	properties.addProperty(&f, "f");
	properties.addProperty(&d, "d");

	const auto& props = properties.getProperties();
	EXPECT_EQ(std::size_t{3}, props.size());

	EXPECT_TRUE(properties.getProperty("i") != nullptr);
	EXPECT_TRUE(properties.getProperty("f") != nullptr);
	EXPECT_TRUE(properties.getProperty("d") != nullptr);
}
