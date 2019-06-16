#include <age/core/Factory.h>
#include <age/navigation/Export.h>
#include <age/navigation/WaypointComponent.h>

AGE_NAVIGATION_EXPORT_C void ComponentFactoryRegister()
{
	AgeFactoryRegister(age::navigation::WaypointComponent).addBaseType<age::entity::Component>();
}
