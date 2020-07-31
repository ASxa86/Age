#pragma once

#include <azule/entity/System.h>

namespace azule
{
	namespace pong
	{
		///
		///	\class PaddleAISystem
		///
		///	\brief This system controls the velocity of the AI paddle based on the position of the ball.
		///
		///	\author Aaron Shelley
		///
		///	\date July 29, 2018
		///
		class PaddleAISystem : public azule::System
		{
		public:
			PaddleAISystem();
			~PaddleAISystem() override;

			void frame(std::chrono::microseconds x);
		};
	}
}
