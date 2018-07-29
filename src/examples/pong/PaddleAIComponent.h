#pragma once

namespace age
{
	namespace entity
	{
		class Entity;
	}

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
		class PaddleAIComponent
		{
		public:
			PaddleAIComponent();
			~PaddleAIComponent();

			///
			///	\brief Set the ball that this paddle is to track and play against.
			///
			void setBall(age::entity::Entity* x);
			age::entity::Entity* getBall() const;

		private:
			age::entity::Entity* ball;
		};
	}
}
