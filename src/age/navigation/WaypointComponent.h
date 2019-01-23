#pragma once

#include <age/math/Vector.h>
#include <age/navigation/Export.h>
#include <vector>

namespace age
{
	namespace navigation
	{
		///
		///	\class WaypointComponent
		///
		///	\brief This component manages a list of waypoints that are used to drive entity pathing.
		///
		///	\date December 13, 2018
		///
		///	\author Aaron Shelley
		///
		struct AGE_NAVIGATION_EXPORT WaypointComponent
		{
			///
			///	\class Waypoint
			///
			///	\brief A single waypoint that is used to determine where to move the entity to.
			///
			struct AGE_NAVIGATION_EXPORT Waypoint
			{
				///
				///	The position to drive the entity toward.
				///
				age::math::Vector Position{};

				///
				///	Mark this waypoint as being processed by the WaypointSystem.
				///
				bool Active{false};
			};

			///
			///	List of waypoints managed by this component.
			///
			std::vector<Waypoint> Waypoints{};

			///
			///	The current waypoint index with respect to ::Waypoints.
			///
			int CurrentWaypoint{0};

			///
			///	Enable looping back to the first waypoint once the last one has been processed.
			///
			bool Loop{false};
		};
	}
}
