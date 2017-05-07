#pragma once

#include <age/core/Event.h>
#include <age/core/Object.h>

namespace age
{
	namespace core
	{
		class EngineState;
		class EventQueue;

		///
		///	\class Engine
		///
		///	\brief The literal engine of AGE. This class is in charge of driving frame updates and managing AGE's state.
		///
		///	This class is the root node of the composite pattern being used within Object. The AGE engine is ran
		/// by calling frame() within a loop.
		///
		///	\date May 5, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT Engine : public Object
		{
		public:
			Engine();
			virtual ~Engine();

			///
			///	Handles updating the engines state and forwarding any queued events.
			///
			virtual void frame();

			void setEngineState(const EngineState& x);
			EngineState getEngineState() const;

			///
			///	Send events synchronously or asynchronously to all registered handlers.
			///
			void sendEvent(std::unique_ptr<Event> x, bool async = false);

			///
			///	Add an event handler to handle sent events from this engine.
			///
			void addEventHandler(const std::function<void(Event*)>& x);

			///
			///	Set a new event queue which will replace the current queue.
			///	Setting a new event queue will delete the current queue clearing any registered event handlers.
			///
			void setEventQueue(std::unique_ptr<EventQueue> x);

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
