#include <age/entity/ComponentFactory.h>
#include <age/navigation/Export.h>
#include <age/navigation/WaypointComponent.h>

using namespace age::entity;
using namespace age::navigation;

AGE_NAVIGATION_EXPORT_C void ComponentFactoryRegister()
{
	ComponentFactory::RegisterType<WaypointComponent>("WaypointComponent");
}
