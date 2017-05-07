#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/core/EngineStateEvent.h>
#include <age/core/EventQueue.h>
#include <age/core/FixedProcessor.h>
#include <age/core/PimplImpl.h>
#include <age/core/VariableProcessor.h>

#include <iostream>
#include <thread>

using namespace age::core;

class Engine::Impl
{
public:
	Impl() : frameStart{std::chrono::steady_clock::now()}, eventQueue{std::make_unique<EventQueue>()}
	{
	}

	std::chrono::time_point<std::chrono::steady_clock> frameStart;
	std::unique_ptr<EventQueue> eventQueue;
	EngineState engineState;
};

Engine::Engine() : Object(), pimpl()
{
}

Engine::~Engine()
{
}

void Engine::frame()
{
	typedef std::chrono::duration<double> seconds;
	// TODO: Change this game loop to a fixed time step with variable rendering (this requires extrapolation of entities).
	const auto currentTime = std::chrono::steady_clock::now();
	const auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - this->pimpl->frameStart);
	this->pimpl->frameStart = currentTime;

	const auto frameTime = std::chrono::duration_cast<seconds>(elapsedTime);
	std::cerr << "FrameT: " << frameTime.count() << "\n";
	std::cerr << "FPS: " << 1.0 / frameTime.count() << "\n";

	const auto fprocessors = this->getChildren<FixedProcessor>();
	const auto vprocessors = this->getChildren<VariableProcessor>();

	for(const auto& fixed : fprocessors)
	{
		fixed->preframe();
	}

	for(const auto& variable : vprocessors)
	{
		variable->preframe();
	}

	this->pimpl->eventQueue->processEvents();

	for(const auto& fixed : fprocessors)
	{
		fixed->frame(elapsedTime);
	}

	for(const auto& variable : vprocessors)
	{
		variable->frame(elapsedTime);
	}

	// Run at 60Hz.
	std::this_thread::sleep_for(seconds(1.0 / 60.0) - std::chrono::duration_cast<seconds>(elapsedTime));
}

void Engine::setEngineState(const EngineState& x)
{
	this->pimpl->engineState = x;
	this->sendEvent(std::make_unique<EngineStateEvent>(this->pimpl->engineState));
}

EngineState Engine::getEngineState() const
{
	return this->pimpl->engineState;
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
