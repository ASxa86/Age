#include <age/core/Factory.h>
#include <age/navigation/Export.h>
#include <age/navigation/WaypointComponent.h>
#include <age/navigation/WaypointSystem.h>

AGE_NAVIGATION_EXPORT_C void FactoryRegister()
{
	AgeFactoryRegister(age::navigation::Waypoint);
	AgeFactoryRegister(age::navigation::WaypointSystem).addBaseType<age::entity::System>();
	AgeFactoryRegister(age::navigation::WaypointComponent).addBaseType<age::entity::Component>();
}
