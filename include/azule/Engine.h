#pragma once

#include <azule/World.h>
#include <azule/SystemPhysics.h>
#include <azule/export.hxx>
#include <chrono>

namespace azule
{
	class AZULE_EXPORT Engine
	{
	public:
		void frame();

		std::chrono::microseconds getFrameTime() const;
		std::chrono::microseconds getFixedFrameTime() const;

		World& getWorld();

	private:
		World world;
		SystemPhysics systemPhysics;
		std::chrono::steady_clock::time_point start{std::chrono::steady_clock::now()};
		std::chrono::microseconds frameTime;
		std::chrono::microseconds fixedFrameTime;
		std::chrono::nanoseconds accumulatedFrameTime;
		int fixedFrameLimit{5};
	};
}
