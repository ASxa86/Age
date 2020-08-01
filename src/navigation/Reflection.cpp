#include <azule/core/Reflection.h>
#include <azule/export.hxx>
#include <azule/navigation/WaypointComponent.h>
#include <azule/navigation/WaypointSystem.h>
#include <azule/utilities/StaticInvoke.h>

using namespace azule;
using namespace azule;

STATIC_INVOKE
{
	Reflection::Instance().add<Waypoint>("Waypoint").addProperty("Position", &Waypoint::Position).addProperty("Active", &Waypoint::Active);

	Reflection::Instance().add<WaypointSystem>("WaypointSystem");

	Reflection::Instance()
		.add<WaypointComponent>("WaypointComponent")
		.addBase<azule::Component>()
		.addProperty("CurrentWaypoint", &WaypointComponent::CurrentWaypoint)
		.addProperty("Loop", &WaypointComponent::Loop);
}
