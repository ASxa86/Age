#include <azule/Engine.h>

using namespace azule;

void Engine::frame()
{
	const auto elapsed = std::chrono::steady_clock::now() - this->start;
	this->frameTime = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
	this->accumulatedFrameTime += elapsed;

	// Variable frame

	// Fixed frame
	decltype(this->fixedFrameLimit) count{};

	while(this->accumulatedFrameTime >= this->fixedFrameTime && count < this->fixedFrameLimit)
	{
		// this->fixedFrameTime;
		this->systemPhysics.frame(*this);
		count++;
	}

	// Render frame
}

std::chrono::microseconds Engine::getFrameTime() const
{
	return this->frameTime;
}

std::chrono::microseconds Engine::getFixedFrameTime() const
{
	return this->fixedFrameTime;
}

World& Engine::getWorld()
{
	return this->world;
}
