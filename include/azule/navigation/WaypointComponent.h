#pragma once

#include <azule/entity/Component.h>
#include <azule/export.h>
#include <azule/math/Vector.h>
#include <vector>

namespace azule
{
	class Entity;

	///
	///	\class Waypoint
	///
	///	\brief A single waypoint that is used to determine where to move the entity to.
	///
	class AZULE_EXPORT Waypoint : public azule::Object
	{
	public:
		Waypoint();

		///
		///	The position to drive the entity toward.
		///
		azule::Vector Position{};

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
	struct AZULE_EXPORT WaypointComponent : public azule::Component
	{
		WaypointComponent();

		///
		///	List of waypoints managed by this component.
		///
		bool addWaypoint(std::unique_ptr<azule::Waypoint> x);

		template <typename T = Waypoint>
		[[maybe_unused]] T* addWaypoint()
		{
			static_assert(std::is_base_of<azule::Entity, T>::value == true, "T must derive from azule::Entity.");

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
