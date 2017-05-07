#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>

#include <mutex>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace age::core;

class EventQueue::Impl
{
public:
	void sendEvent(Event* x)
	{
		for(const auto& handler : this->handlers)
		{
			handler(x);
		}
	}

	std::vector<std::function<void(Event*)>> handlers;
	std::queue<std::unique_ptr<Event>> queue;
	std::mutex queueMutex;
};

EventQueue::EventQueue() : pimpl()
{
}

EventQueue::~EventQueue()
{
}

void EventQueue::addEventHandler(const std::function<void(Event*)>& x)
{
	this->pimpl->handlers.push_back(x);
}

void EventQueue::sendEvent(std::unique_ptr<Event> x)
{
	if(x != nullptr)
	{
		this->pimpl->sendEvent(x.get());
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
		this->pimpl->sendEvent(event.get());
		this->pimpl->queue.pop();
	}
}
