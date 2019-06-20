#include <age/core/Timer.h>

#include<gtest/gtest.h>
#include <thread>

using namespace age::core;

TEST(Timer, reset)
{
	Timer timer;

	// I couldn't use EXPECT_NEAR due to implicit conversion from __int64 to double.
	// Instead, I constructed an upper and lower bound based on a small tolerance
	// which I then compared my deltas against. As sleeping is not precise, if we're
	// within the bounds, we are good.
	const auto sleep = std::chrono::microseconds(100000);
	const auto tolerance = std::chrono::microseconds(1000);
	const auto lower = sleep - tolerance;
	const auto upper = sleep + tolerance;

	std::this_thread::sleep_for(sleep);

	{
		const auto elapsed = timer.reset();
		EXPECT_LT(elapsed, upper);
		EXPECT_GT(elapsed, lower);
	}

	std::this_thread::sleep_for(sleep);

	{
		const auto elapsed = timer.reset();
		EXPECT_LT(elapsed, upper);
		EXPECT_GT(elapsed, lower);
	}
}

TEST(Timer, seconds)
{
	const auto us = std::chrono::microseconds(10000);
	const auto seconds = std::chrono::duration_cast<age::core::seconds>(us);
	EXPECT_EQ(0.01, seconds.count());

	const auto us16 = std::chrono::microseconds(16667);
	const auto seconds16 = std::chrono::duration_cast<age::core::seconds>(us16);
	EXPECT_EQ(0.016667, seconds16.count());
}
