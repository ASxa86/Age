#include <age/core/Reflection.h>
#include <age/navigation/Export.h>
#include <age/navigation/WaypointComponent.h>
#include <age/navigation/WaypointSystem.h>
#include <age/utilities/StaticInvoke.h>

using namespace age::core;
using namespace age::navigation;

STATIC_INVOKE
{
	Reflection::Instance().add<Waypoint>("Waypoint").addProperty("Position", &Waypoint::Position).addProperty("Active", &Waypoint::Active);

	Reflection::Instance().add<WaypointSystem>("WaypointSystem");

	Reflection::Instance()
		.add<WaypointComponent>("WaypointComponent")
		.addBase<age::entity::Component>()
		.addProperty("CurrentWaypoint", &WaypointComponent::CurrentWaypoint)
		.addProperty("Loop", &WaypointComponent::Loop);
}
