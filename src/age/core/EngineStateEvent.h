#pragma once

#include <age/core/Event.h>
#include <age/core/EngineState.h>

namespace age
{
	namespace core
	{
		///
		///	\class EngineStateEvent
		///
		///	\brief Event to notify an engine state change.
		///
		///	\date May 7, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT EngineStateEvent : public Event
		{
		public:
			///
			///	\param EngineState The new engine state.
			///
			EngineStateEvent(const EngineState& x);
			~EngineStateEvent() override;

			const EngineState& getEngineState() const;

		private:
			EngineState engineState;
		};
	}
}
