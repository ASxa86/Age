#include <age/core/Factory.h>
#include <age/entity/AnimationComponent.h>
#include <age/entity/CloneSystem.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/entity/HealthComponent.h>
#include <age/entity/Export.h>
#include <age/entity/SelectionComponent.h>
#include <age/entity/TransformComponent.h>

AGE_ENTITY_EXPORT_C void FactoryRegister()
{
	AgeFactoryRegister(age::entity::Entity);
	AgeFactoryRegister(age::entity::EntityDatabase);
	AgeFactoryRegister(age::entity::SelectionComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::entity::TransformComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::entity::HealthComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::entity::AnimationComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::entity::CloneSystem).addBaseType<age::entity::System>();
}
