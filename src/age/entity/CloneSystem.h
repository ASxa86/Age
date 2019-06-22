#pragma once

#include <age/entity/System.h>

namespace age
{
	namespace entity
	{
		///
		///	\class CloneSystem
		///
		///	\brief Clone and add an entity at a given rate for a given limit.
		///
		///	\date June 22, 2019
		///
		///	\author Aaron Shelley
		///
		class AGE_ENTITY_EXPORT CloneSystem : public System
		{
		public:
			CloneSystem();
			void frame(std::chrono::microseconds x);

			///
			///	\brief Define the rate at which to clone the child entity.
			///
			std::chrono::microseconds Rate{0};

			///
			///	\brief Define the number of entities this system is to generate.
			///
			int Limit{-1};

			///
			///	\brief Define the number of entities this system has generated.
			///
			///	Once the count has reached the limit, no more entities will be made.
			///
			int Count{0};

		private:
			std::chrono::microseconds elapsed{0};
		};
	}
}
