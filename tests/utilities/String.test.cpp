#include <gtest/gtest.h>

#include <azule/utilities/String.h>

using namespace azule;

namespace
{
	enum class TestEnum : int
	{
		One,
		Two,
		Three
	};

	struct TestClass
	{
		enum class TestEnum : int
		{
			One,
			Two,
			Three,
			Four
		};
	};
}

TEST(String, ToStringBool)
{
	{
		constexpr bool x = true;
		EXPECT_EQ("true", ToString(x));
	}

	{
		constexpr bool x = false;
		EXPECT_EQ("false", ToString(x));
	}
}

TEST(String, ToStringInt)
{
	constexpr int x = 1;
	EXPECT_EQ("1", ToString(x));
}

TEST(String, ToStringFloat)
{
	constexpr float x = 1.0;
	EXPECT_EQ("1.0", ToString(x));
}

TEST(String, ToStringDouble)
{
	constexpr double x = 1.0;
	EXPECT_EQ("1.0", ToString(x));
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

TEST(String, StringToBool)
{
	{
		const std::string x = "true";
		EXPECT_EQ(true, StringTo<bool>(x));
	}

	{
		const std::string x = "false";
		EXPECT_EQ(false, StringTo<bool>(x));
	}
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
