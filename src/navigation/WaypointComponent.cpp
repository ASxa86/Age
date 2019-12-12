#include <age/navigation/WaypointComponent.h>

using namespace age::navigation;

Waypoint::Waypoint()
{
	this->addProperty(this->Position, "Position");
	this->addProperty(this->Active, "Active");
}

WaypointComponent::WaypointComponent() : age::entity::Component()
{
	this->addProperty(this->CurrentWaypoint, "CurrentWaypoint");
	this->addProperty(this->Loop, "Loop");
}

bool WaypointComponent::addWaypoint(std::unique_ptr<age::navigation::Waypoint> x)
{
	return this->addChild(std::move(x));
}
