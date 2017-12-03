#include <age/core/EventQueue.h>
#include <age/core/Object.h>
#include <age/core/PimplImpl.h>
#include <boost/signals2/signal.hpp>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace age::core;

class EventQueue::Impl
{
public:
	boost::signals2::signal<void(Event*)> handlers;
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

boost::signals2::connection EventQueue::addEventHandler(std::function<void(Event*)> x, Object* tracked)
{
	boost::signals2::signal<void(Event*)>::slot_type slot(x);

	if(tracked != nullptr)
	{
		slot.track_foreign(tracked->shared_from_this());
	}

	return this->pimpl->handlers.connect(slot);
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
