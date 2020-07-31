#include <azule/core/EngineStateEvent.h>

using namespace azule;

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
