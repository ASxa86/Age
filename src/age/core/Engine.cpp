#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/core/EngineStateEvent.h>
#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/core/Processor.h>
#include <age/core/Timer.h>
#include <thread>

using namespace age::core;

class Engine::Impl
{
public:
	Impl() : eventQueue{std::make_unique<EventQueue>()}, fixedDelta{10000}, accumulatedDelta{0}, fixedFrameLimit{5}
	{
	}

	std::unique_ptr<EventQueue> eventQueue;
	Timer timer;
	std::chrono::microseconds fixedDelta;
	std::chrono::microseconds accumulatedDelta;
	EngineState engineState;

	/// Set max number of frames to process before moving on.
	/// Helps prevent getting stuck updating frames on slow machines.
	uint8_t fixedFrameLimit;
};

Engine::Engine() : Object(), pimpl()
{
}

Engine::~Engine()
{
}

void Engine::frame()
{
	const auto elapsed = this->pimpl->timer.reset();
	this->pimpl->accumulatedDelta += elapsed;
	const auto processors = this->getChildren<Processor>();

	// Once the events have been queued, send them on their way.
	this->pimpl->eventQueue->processEvents();

	// The engine's variable update frame(). This frame is called on every engine frame.
	// This is good for handling non-physics movement, keyboard/joystick input, and any other
	// non-physics related logic.
	for(const auto& processor : processors)
	{
		processor->variable(elapsed);
	}

	decltype(this->pimpl->fixedFrameLimit) count{0};

	// The engine's fixed update frame(). This will loop until the accumulated time has been consumed
	// or the max frame limit has been reached. This guarantees a fixed time step and that we don't
	// get stuck processing frames indefinitely.
	while(this->pimpl->accumulatedDelta >= this->pimpl->fixedDelta && count < this->pimpl->fixedFrameLimit)
	{
		for(const auto& processor : processors)
		{
			processor->fixed(this->pimpl->fixedDelta);
		}

		this->pimpl->accumulatedDelta -= this->pimpl->fixedDelta;
		count++;
	}

	for(const auto& processor : processors)
	{
		// Render a graphics frame passing in the time between frames that can be used for extrapolating
		// the engine's state.
		processor->render(std::chrono::microseconds(this->pimpl->accumulatedDelta / this->pimpl->fixedDelta));
	}
}

void Engine::setEngineState(const EngineState& x)
{
	this->pimpl->engineState = x;

	switch(this->pimpl->engineState.getState())
	{
		case EngineState::State::Initialize:
			for(const auto& child : this->getChildren(true))
			{
				child->initialize();
			}
			break;
		case EngineState::State::Run:
		case EngineState::State::Pause:
		case EngineState::State::Exit:
		case EngineState::State::Unknown:
		default:
			break;
	}

	// this->sendEvent(std::make_unique<EngineStateEvent>(this->pimpl->engineState));
}

EngineState Engine::getEngineState() const
{
	return this->pimpl->engineState;
}

void Engine::setFixedDelta(std::chrono::microseconds x)
{
	this->pimpl->fixedDelta = x;
}

void Engine::setFixedFrameLimit(uint8_t x)
{
	this->pimpl->fixedFrameLimit = x;
}

void Engine::sendEvent(std::unique_ptr<Event> x, bool async)
{
	if(async == true)
	{
		this->pimpl->eventQueue->queueEvent(std::move(x));
	}
	else
	{
		this->pimpl->eventQueue->sendEvent(std::move(x));
	}
}

void Engine::addEventHandler(const std::function<void(Event*)>& x)
{
	this->pimpl->eventQueue->addEventHandler(x);
}

void Engine::setEventQueue(std::unique_ptr<EventQueue> x)
{
	this->pimpl->eventQueue = std::move(x);
}
