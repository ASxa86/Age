#pragma once

#include <age/entity/System.h>

namespace age
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
		class PaddleAISystem : public age::entity::System
		{
		public:
			PaddleAISystem();
			~PaddleAISystem() override;

			void frame(std::chrono::microseconds x);
		};
	}
}
