#pragma once

#include <age/entity/System.h>
#include <age/navigation/export.h>

namespace age
{
	namespace navigation
	{
		///
		///	\class WaypointSystem
		///
		///	\brief A system used to process entity waypoints and control entity velocities to achieve those waypoints.
		///
		///	\date January 21, 2019
		///
		///	\author Aaron Shelley
		///
		class AGE_NAVIGATION_EXPORT WaypointSystem : public age::entity::System
		{
		public:
			WaypointSystem();
			~WaypointSystem() override;

			void frame(std::chrono::microseconds x);
		};
	}
}
