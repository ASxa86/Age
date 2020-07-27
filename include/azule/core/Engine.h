#pragma once

#include <azule/core/Event.h>
#include <azule/core/Object.h>
#include <azule/utilities/Pimpl.h>
#include <chrono>

namespace azule
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
		class AZULE_CORE_EXPORT Engine : public Object
		{
		public:
			Engine();
			~Engine() override;

			///
			///	Handles updating the engines state and forwarding any queued events.
			///
			void frame();

			///
			///	Set the engines state.
			///
			///	Setting the state will cause an event to be sent to all registered handlers.
			///
			void setEngineState(const EngineState& x);

			///
			///	Get the current state of the engine.
			///
			EngineState getEngineState() const;

			///
			///	Set the fixed rate at which to run fixed frames. Default 100Hz.
			///
			///	This does not effect graphical frame rate.
			///
			void setFixedDelta(std::chrono::microseconds x);

			///
			///	Set the maximum number of fixed frames that can be processed within a single engine frame.
			///
			///	Depending on the amount of time between engine frames, a number of fixed frames could run to catch up to
			///	the amount of time that has elapsed. In order to prevent increasing the time between engine frames on slower machines,
			///	a fixed frame limit is provided.
			///	Default 5.
			///
			void setFixedFrameLimit(uint8_t x);

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
