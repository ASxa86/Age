#include <age/navigation/WaypointComponent.h>

using namespace age::navigation;

Waypoint::Waypoint()
{
}

WaypointComponent::WaypointComponent() : age::entity::Component()
{
}

bool WaypointComponent::addWaypoint(std::unique_ptr<age::navigation::Waypoint> x)
{
	return this->addChild(std::move(x));
}
