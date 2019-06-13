#pragma once

#include <age/entity/Component.h>
#include <age/entity/Entity.h>

namespace age
{
	namespace pong
	{
		///
		///	\class PaddleAIComponent
		///
		///	\brief Mark a paddle entity as AI so that the PaddleAISystem can drive it.
		///
		///	\author Aaron Shelley
		///
		///	\date July 29, 2018
		///
		class PaddleAIComponent : public age::entity::Component
		{
		public:
			PaddleAIComponent();
			~PaddleAIComponent();

			///
			///	\brief Set the ball that this paddle is to track and play against.
			///
			void setBall(age::entity::Entity x);
			const age::entity::Entity& getBall() const;

		private:
			age::entity::Entity ball;
		};
	}
}
