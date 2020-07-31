#include <azule/core/EventQueue.h>
#include <azule/core/Object.h>
#include <azule/utilities/PimplImpl.h>
#include <azule/utilities/Signal.h>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace azule;
using namespace azule;

class EventQueue::Impl
{
public:
	Signal<Event*> handlers;
	std::queue<std::unique_ptr<Event>> queue;
	std::mutex queueMutex;
};

EventQueue::EventQueue() : pimpl()
{
}

EventQueue::~EventQueue()
{
}

EventQueue& EventQueue::Instance()
{
	static EventQueue singleton;
	return singleton;
}

ScopedConnection EventQueue::addEventHandler(std::function<void(Event*)> x)
{
	return this->pimpl->handlers.connect_scoped(x);
}

void EventQueue::sendEvent(std::unique_ptr<Event> x)
{
	if(x != nullptr)
	{
		this->pimpl->handlers(x.get());
	}
}

void EventQueue::queueEvent(std::unique_ptr<Event> x)
{
	if(x != nullptr)
	{
		std::lock_guard<std::mutex> lock(this->pimpl->queueMutex);
		this->pimpl->queue.push(std::move(x));
	}
}

void EventQueue::processEvents()
{
	std::lock_guard<std::mutex> lock(this->pimpl->queueMutex);

	while(this->pimpl->queue.empty() == false)
	{
		const auto& event = this->pimpl->queue.front();
		this->pimpl->handlers(event.get());
		this->pimpl->queue.pop();
	}
}
