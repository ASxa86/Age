#pragma once

#include <age/core/Event.h>
#include <age/core/Pimpl.h>
#include <boost/signals2/connection.hpp>
#include <functional>

namespace age
{
	namespace core
	{
		class Event;
		class Object;

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
			~EventQueue();

			EventQueue(const EventQueue&) = delete;
			EventQueue& operator=(const EventQueue&) = delete;

			static EventQueue& Instance();

			///
			///	\brief Register an event handler for any events.
			///
			boost::signals2::connection addEventHandler(std::function<void(Event*)> x, Object* tracked = nullptr);

			///
			///	\brief Sends the event directly to registered handlers.
			///
			///	Ownership of the event is passed to this function which will be destroyed on return.
			///
			void sendEvent(std::unique_ptr<Event> x);

			///
			///	\brief Queues the event to be sent on the next call to processEvents().
			///
			///	Ownership of the event is given to the queue which will be destroyed on return of the next call to processEvents().
			///
			///	Thread-safe.
			///
			void queueEvent(std::unique_ptr<Event> x);

			///
			///	\brief Sends all queued events to registered handlers.
			///
			///	Thread-safe.
			///
			void processEvents();

		private:
			EventQueue();

			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
