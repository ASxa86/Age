#include <gtest/gtest.h>
#include <azule/utilities/TypeName.h>

#define STRINGIFY(T) #T

namespace azule
{
	namespace test
	{
		struct TestOne
		{
		};
	}
}

TEST(Utilities, TypeNameTemplate)
{
	EXPECT_EQ(azule::TypeName<azule::test::TestOne>(), STRINGIFY(azule::test::TestOne));
}

TEST(Utilities, TypeNameTypeID)
{
	EXPECT_EQ(azule::TypeName(typeid(azule::test::TestOne)), STRINGIFY(azule::test::TestOne));
}
