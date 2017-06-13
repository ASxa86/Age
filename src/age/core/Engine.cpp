#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/core/EngineStateEvent.h>
#include <age/core/EventQueue.h>
#include <age/core/FixedSystem.h>
#include <age/core/PimplImpl.h>
#include <age/core/Timer.h>
#include <age/core/RenderSystem.h>
#include <age/core/VariableSystem.h>

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
	const auto fsystems = this->getChildren<FixedSystem>();
	const auto rsystems = this->getChildren<RenderSystem>();
	const auto vsystems = this->getChildren<VariableSystem>();

	// Poll for events such as controller inputs so we can send the events
	// to any systems that may require them to update the engine's state.
	for(const auto& render : rsystems)
	{
		render->pollEvents();
	}

	// Once the events have been queued, send them on their way.
	this->pimpl->eventQueue->processEvents();

	// The engine's variable update frame(). This frame is called on every engine frame.
	// This is good for handling non-physics movement, keyboard/joystick input, and any other
	// non-physics related logic.
	for(const auto& variable : vsystems)
	{
		variable->frame(elapsed);
	}

	decltype(this->pimpl->fixedFrameLimit) count{0};

	// The engine's fixed update frame(). This will loop until the accumulated time has been consumed
	// or the max frame limit has been reached. This guarantees a fixed time step and that we don't
	// get stuck processing frames indefinitely.
	while(this->pimpl->accumulatedDelta >= this->pimpl->fixedDelta && count < this->pimpl->fixedFrameLimit)
	{
		for(const auto& fixed : fsystems)
		{
			fixed->frame(this->pimpl->fixedDelta);
		}

		this->pimpl->accumulatedDelta -= this->pimpl->fixedDelta;
		count++;
	}

	for(const auto& render : rsystems)
	{
		// Render a graphics frame passing in the time between frames that can be used for extrapolating
		// the engine's state.
		render->frame(std::chrono::microseconds(this->pimpl->accumulatedDelta / this->pimpl->fixedDelta));
	}
}

void Engine::setEngineState(const EngineState& x)
{
	const auto systems = this->getChildren<System>();

	this->pimpl->engineState = x;

	switch(this->pimpl->engineState.getState())
	{
		case EngineState::State::Initialize:
			for(const auto& system : systems)
			{
				system->initialize();
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
