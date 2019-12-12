#include <age/entity/AnimationComponent.h>
#include <age/entity/ComponentFactory.h>
#include <age/entity/Export.h>
#include <age/entity/TransformComponent.h>

using namespace age::entity;

AGE_ENTITY_EXPORT_C void ComponentFactoryRegister()
{
	ComponentFactory::RegisterType<TransformComponent>("TransformComponent");
	ComponentFactory::RegisterType<AnimationComponent>("AnimationComponent");
}
