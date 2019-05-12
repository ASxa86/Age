#include <gtest/gtest.h>

#include <age/core/MetaEnum.h>
#include <age/core/String.h>

using namespace age::core;

namespace
{
	MetaEnumClass(TestEnum, int, One, Two, Three);

	struct TestClass
	{
		MetaEnumClassNested(TestEnum, int, One, Two, Three);
	};
}

TEST(String, ToStringInt)
{
	constexpr int x = 1;
	EXPECT_EQ("1", ToString(x));
}

TEST(String, ToStringFloat)
{
	constexpr float x = 1.0;
	EXPECT_EQ("1", ToString(x));
}

TEST(String, ToStringDouble)
{
	constexpr double x = 1.0;
	EXPECT_EQ("1", ToString(x));
}

TEST(String, ToStringEnum)
{
	constexpr TestEnum x = TestEnum::One;
	EXPECT_EQ("One", ToString(x));
}

TEST(String, ToStringEnumNested)
{
	constexpr TestClass::TestEnum x = TestClass::TestEnum::One;
	EXPECT_EQ("One", ToString(x));
}

TEST(String, StringToInt)
{
	const std::string x = "1";
	EXPECT_EQ(1, StringTo<int>(x));
}

TEST(String, StringToFloat)
{
	const std::string x = "1.0f";
	EXPECT_FLOAT_EQ(1.0f, StringTo<float>(x));
}

TEST(String, StringToDouble)
{
	const std::string x = "1.0";
	EXPECT_DOUBLE_EQ(1.0, StringTo<double>(x));
}

TEST(String, StringToEnum)
{
	const std::string x = "One";
	EXPECT_EQ(TestEnum::One, StringTo<TestEnum>(x));
}

TEST(String, StringToEnumNested)
{
	const std::string x = "One";
	EXPECT_EQ(TestClass::TestEnum::One, StringTo<TestClass::TestEnum>(x));
}
