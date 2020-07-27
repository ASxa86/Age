#include <azule/navigation/WaypointComponent.h>

using namespace azule::navigation;

Waypoint::Waypoint()
{
}

WaypointComponent::WaypointComponent() : azule::entity::Component()
{
}

bool WaypointComponent::addWaypoint(std::unique_ptr<azule::navigation::Waypoint> x)
{
	return this->addChild(std::move(x));
}
