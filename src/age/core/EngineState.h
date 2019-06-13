#pragma once

#include <age/core/Export.h>
#include <chrono>
#include <cstdint>

namespace age
{
	namespace core
	{
		///
		///	\class EngineState
		///
		///	\brief This class manages the state of the entire engine.
		///
		///	\date May 7, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT EngineState
		{
		public:
			///
			///	\enum State
			///
			///	This describes the different types of states the engine could be in.
			///
			enum class State : uint8_t
			{
				Unknown,
				Initialize,
				Run,
				Pause,
				Exit
			};

			EngineState(State x = State::Unknown);
			~EngineState();

			void setState(State x);
			State getState() const;

			void setSimTime(std::chrono::microseconds x);
			std::chrono::microseconds getSimTime() const;

			void setFrameCount(int x);
			int getFrameCount() const;

		private:
			State state;
			std::chrono::microseconds simTime;
			int frameCount;
		};
	}
}
