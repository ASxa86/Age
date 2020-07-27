#pragma once

#include <azule/entity/Component.h>
#include <azule/entity/Entity.h>

namespace azule
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
		class PaddleAIComponent : public azule::entity::Component
		{
		public:
			PaddleAIComponent();
			~PaddleAIComponent();

			///
			///	\brief Set the ball that this paddle is to track and play against.
			///
			void setBall(azule::entity::Entity x);
			const azule::entity::Entity& getBall() const;

		private:
			azule::entity::Entity ball;
		};
	}
}
