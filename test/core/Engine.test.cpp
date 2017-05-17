#include <age/core/Engine.h>
#include <gtest/gtest.h>

using namespace age::core;

TEST(Engine, Constructor)
{
	EXPECT_NO_THROW(Engine());
	EXPECT_NO_THROW(std::make_unique<Engine>());
	EXPECT_TRUE(std::make_unique<Engine>() != nullptr);
}