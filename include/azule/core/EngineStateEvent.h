#pragma once

#include <azule/core/Event.h>
#include <azule/core/EngineState.h>

namespace azule
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
		class AZULE_CORE_EXPORT EngineStateEvent : public Event
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
