#include <azule/core/EngineStateEvent.h>

using namespace azule::core;

EngineStateEvent::EngineStateEvent(const EngineState& x) : engineState{x}
{
}

EngineStateEvent::~EngineStateEvent()
{
}

const EngineState& EngineStateEvent::getEngineState() const
{
	return this->engineState;
}
