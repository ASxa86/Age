#include <age/navigation/WaypointComponent.h>

using namespace age::navigation;

WaypointComponent::WaypointComponent() : age::entity::Component()
{
	this->addProperty(this->CurrentWaypoint, "CurrentWaypoint");
	this->addProperty(this->Loop, "Loop");
}
