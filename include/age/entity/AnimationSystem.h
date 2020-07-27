#pragma once

#include <age/entity/System.h>

namespace age
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
		class AGE_ENTITY_EXPORT AnimationSystem : public System
		{
		public:
			AnimationSystem();
			~AnimationSystem() override;
			void frame(std::chrono::microseconds x);
		};
	}
}
