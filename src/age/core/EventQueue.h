#pragma once

#include <age/core/Event.h>
#include <age/core/Pimpl.h>
#include <functional>

namespace age
{
	namespace core
	{
		class Event;

		///
		///	\class EventQueue
		///
		///	\brief Manages the sending and receiving of events to registered event handlers.
		///
		///	\date May 5, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT EventQueue
		{
		public:
			EventQueue();
			virtual ~EventQueue();

			///
			///	\brief Register an event handler for any events.
			///
			virtual void addEventHandler(const std::function<void(Event*)>& x);

			///
			///	\brief Sends the event directly to registered handlers.
			///
			///	Ownership of the event is passed to this function which will be destroyed on return.
			///
			virtual void sendEvent(std::unique_ptr<Event> x);

			///
			///	\brief Queues the event to be sent on the next call to processEvents().
			///
			///	Ownership of the event is given to the queue which will be destroyed on return of the next call to processEvents().
			///
			///	Thread-safe.
			///
			virtual void queueEvent(std::unique_ptr<Event> x);

			///
			///	\brief Sends all queued events to registered handlers.
			///
			///	Thread-safe.
			///
			virtual void processEvents();

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}