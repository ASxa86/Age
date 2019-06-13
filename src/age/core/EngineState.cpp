#include <age/core/EngineState.h>

using namespace age::core;

EngineState::EngineState(State x) : state{x}, simTime{0}, frameCount{0}
{
}

EngineState::~EngineState()
{
}

void EngineState::setState(State x)
{
	this->state = x;
}

EngineState::State EngineState::getState() const
{
	return this->state;
}

void EngineState::setSimTime(std::chrono::microseconds x)
{
	this->simTime = x;
}

std::chrono::microseconds EngineState::getSimTime() const
{
	return this->simTime;
}

void EngineState::setFrameCount(int x)
{
	this->frameCount = x;
}

int EngineState::getFrameCount() const
{
	return frameCount;
}
