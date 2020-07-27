#pragma once

#include <age/entity/Component.h>
#include <age/math/Vector.h>
#include <age/navigation/export.h>
#include <vector>

namespace age
{
	namespace entity
	{
		class Entity;
	}
}

namespace age
{
	namespace navigation
	{
		///
		///	\class Waypoint
		///
		///	\brief A single waypoint that is used to determine where to move the entity to.
		///
		class AGE_NAVIGATION_EXPORT Waypoint : public age::core::Object
		{
		public:
			Waypoint();

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
		///	\class WaypointComponent
		///
		///	\brief This component manages a list of waypoints that are used to drive entity pathing.
		///
		///	\date December 13, 2018
		///
		///	\author Aaron Shelley
		///
		struct AGE_NAVIGATION_EXPORT WaypointComponent : public age::entity::Component
		{
			WaypointComponent();

			///
			///	List of waypoints managed by this component.
			///
			bool addWaypoint(std::unique_ptr<age::navigation::Waypoint> x);

			template <typename T = Waypoint>
			[[maybe_unused]] T* addWaypoint()
			{
				static_assert(std::is_base_of<age::entity::Entity, T>::value == true, "T must derive from age::entity::Entity.");

				auto child = std::make_unique<T>();
				const auto p = child.get();

				if(this->addWaypoint(std::move(child)) == true)
				{
					return p;
				}

				return nullptr;
			}

			///
			///	The current waypoint index with respect to ::Waypoints.
			///
			int CurrentWaypoint{0};

			///
			///	Enable looping back to the first waypoint once the last one has been processed.
			///
			bool Loop{false};

		private:
			using Object::addChild;
		};
	}
}
