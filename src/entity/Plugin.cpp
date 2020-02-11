#include <age/core/Factory.h>
#include <age/entity/AnimationComponent.h>
#include <age/entity/CloneSystem.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/entity/HealthComponent.h>
#include <age/entity/Export.h>
#include <age/entity/SelectionComponent.h>
#include <age/entity/TransformComponent.h>
#include <age/utilities/StaticInvoke.h>
#include <age/utilities/Reflection.h>

using namespace age::utilities;

STATIC_INVOKE
{
	AgeFactoryRegister(age::entity::Entity);
	AgeFactoryRegister(age::entity::EntityDatabase);
	AgeFactoryRegister(age::entity::SelectionComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::entity::TransformComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::entity::HealthComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::entity::AnimationComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::entity::CloneSystem).addBaseType<age::entity::System>();

	auto& refl = Reflection::Add<age::entity::SelectionComponent>("SelectionComponent");
	refl.addBase<age::entity::Component>();
	refl.addProperty("Selected", &age::entity::SelectionComponent::Selected);

	refl = Reflection::Add<age::entity::TransformComponent>("TransformComponent");
	refl.addBase<age::entity::Component>();
	refl.addProperty("Position", &age::entity::TransformComponent::Position);
	refl.addProperty("Rotation", &age::entity::TransformComponent::Rotation);

	refl = Reflection::Add<age::entity::HealthComponent>("HealthComponent");
	refl.addBase<age::entity::Component>();
	refl.addProperty("HealthMax", &age::entity::HealthComponent::HealthMax);
	refl.addProperty("Health", &age::entity::HealthComponent::Health);

	refl = Reflection::Add<age::entity::AnimationComponent>("AnimationComponent");
	refl.addBase<age::entity::Component>();
}
