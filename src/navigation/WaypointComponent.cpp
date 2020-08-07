#include <azule/navigation/WaypointComponent.h>

using namespace azule;

Waypoint::Waypoint()
{
	this->addProperty("Active", this->Active);
	this->addProperty("Position", this->Position);
}

WaypointComponent::WaypointComponent() : azule::Component()
{
	this->addProperty("CurrentWaypoint", this->CurrentWaypoint);
	this->addProperty("Loop", this->Loop);
}

bool WaypointComponent::addWaypoint(std::unique_ptr<azule::Waypoint> x)
{
	return this->addChild(std::move(x));
}
