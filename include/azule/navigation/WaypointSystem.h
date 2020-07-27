#pragma once

#include <azule/entity/System.h>
#include <azule/navigation/export.h>

namespace azule
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
		class AZULE_NAVIGATION_EXPORT WaypointSystem : public azule::entity::System
		{
		public:
			WaypointSystem();
			~WaypointSystem() override;

			void frame(std::chrono::microseconds x);
		};
	}
}
