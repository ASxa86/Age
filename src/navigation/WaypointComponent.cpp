#include <azule/navigation/WaypointComponent.h>

using namespace azule;

Waypoint::Waypoint()
{
}

WaypointComponent::WaypointComponent() : azule::Component()
{
}

bool WaypointComponent::addWaypoint(std::unique_ptr<azule::Waypoint> x)
{
	return this->addChild(std::move(x));
}
