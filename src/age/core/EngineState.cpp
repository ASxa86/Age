#include <age/core/EngineState.h>

using namespace age::core;

EngineState::EngineState(State x) : state{x}
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
