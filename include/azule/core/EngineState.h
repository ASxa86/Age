#pragma once

#include <azule/export.h>
#include <chrono>
#include <cstdint>

namespace azule
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
		class AZULE_EXPORT EngineState
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
				StartUp,
				Run,
				Pause,
				Shutdown
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
