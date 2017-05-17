#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/core/EngineStateEvent.h>
#include <age/core/EventQueue.h>
#include <age/core/FixedProcessor.h>
#include <age/core/PimplImpl.h>
#include <age/core/Timer.h>
#include <age/core/RenderProcessor.h>

#include <iostream>
#include <thread>

using namespace age::core;

class Engine::Impl
{
public:
	Impl() : eventQueue{std::make_unique<EventQueue>()}, fixedDelta{10000}, frameSkip{5}, accumulatedDelta{0}
	{
	}

	std::unique_ptr<EventQueue> eventQueue;
	Timer timer;
	std::chrono::microseconds fixedDelta;
	std::chrono::microseconds accumulatedDelta;
	EngineState engineState;

	/// Set max number of frames to process before moving on.
	/// Helps prevent getting stuck updating frames on slow machines.
	const size_t frameSkip;
};

Engine::Engine() : Object{}, pimpl{}
{
}

Engine::~Engine()
{
}

void Engine::frame()
{
	this->pimpl->accumulatedDelta += this->pimpl->timer.reset();
	const auto fprocessors = this->getChildren<FixedProcessor>();
	const auto rprocessors = this->getChildren<RenderProcessor>();

	for(const auto& render : rprocessors)
	{
		render->pollEvents();
	}

	this->pimpl->eventQueue->processEvents();

	size_t count{0};

	while(this->pimpl->accumulatedDelta >= this->pimpl->fixedDelta && count < this->pimpl->frameSkip)
	{
		for(const auto& fixed : fprocessors)
		{
			fixed->frame(this->pimpl->fixedDelta);
		}

		this->pimpl->accumulatedDelta -= this->pimpl->fixedDelta;
		count++;
	}

	for(const auto& render : rprocessors)
	{
		render->frame(std::chrono::microseconds(this->pimpl->accumulatedDelta / this->pimpl->fixedDelta));
	}
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

void Engine::setFixedDelta(std::chrono::microseconds x)
{
	this->pimpl->fixedDelta = x;
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
