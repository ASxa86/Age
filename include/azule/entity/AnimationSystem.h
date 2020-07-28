#pragma once

#include <azule/entity/System.h>

namespace azule
{
	namespace entity
	{
		///
		///	\class AnimationSystem
		///
		///	\brief A system for processing AnimationComponents of entities.
		///
		///	\date September 27, 2018
		///
		///	\author Aaron Shelley
		///
		class AZULE_EXPORT AnimationSystem : public System
		{
		public:
			AnimationSystem();
			~AnimationSystem() override;
			void frame(std::chrono::microseconds x);
		};
	}
}
