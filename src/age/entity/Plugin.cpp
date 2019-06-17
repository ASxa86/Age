#include <age/core/Factory.h>
#include <age/entity/AnimationComponent.h>
#include <age/entity/Export.h>
#include <age/entity/TransformComponent.h>

AGE_ENTITY_EXPORT_C void FactoryRegister()
{
	AgeFactoryRegister(age::entity::TransformComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::entity::AnimationComponent).addBaseType<age::entity::Component>();
}
