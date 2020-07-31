#include <azule/core/Engine.h>
#include <gtest/gtest.h>

using namespace azule::core;

TEST(Engine, Constructor)
{
	EXPECT_NO_THROW(Engine());
	EXPECT_NO_THROW(auto m = std::make_unique<Engine>());
	EXPECT_TRUE(std::make_unique<Engine>() != nullptr);
}
