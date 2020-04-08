#include <age/core/Reflection.h>
#include <age/entity/AnimationComponent.h>
#include <age/entity/CloneSystem.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/entity/HealthComponent.h>
#include <age/entity/SelectionComponent.h>
#include <age/entity/TransformComponent.h>
#include <age/utilities/StaticInvoke.h>

using namespace age::core;
using namespace age::entity;

STATIC_INVOKE
{
	Reflection::Instance().add<Entity>("Entity").addBase<Object>();

	Reflection::Instance().add<EntityDatabase>("EntityDatabase").addBase<Object>();

	Reflection::Instance().add<System>("System").addBase<Object>();

	Reflection::Instance()
		.add<CloneSystem>("CloneSystem")
		.addBase<System>()
		.addProperty("Rate", &CloneSystem::Rate)
		.addProperty("Limit", &CloneSystem::Limit)
		.addProperty("Count", &CloneSystem::Count);

	Reflection::Instance().add<Component>("Component").addBase<Object>().addProperty("Enabled", &Component::Enabled);

	Reflection::Instance()
		.add<AnimationComponent>("AnimationComponent")
		.addBase<Component>()
		.addMethod("Length", &AnimationComponent::setLength, &AnimationComponent::getLength)
		.addMethod("Elapsed", &AnimationComponent::setElapsed, &AnimationComponent::getElapsed)
		.addMethod("Speed", &AnimationComponent::setSpeed, &AnimationComponent::getSpeed);

	Reflection::Instance()
		.add<HealthComponent>("HealthComponent")
		.addBase<Component>()
		.addProperty("Health", &HealthComponent::Health)
		.addProperty("HealthMax", &HealthComponent::HealthMax);

	Reflection::Instance().add<SelectionComponent>("SelectionComponent").addBase<Component>().addProperty("Selected", &SelectionComponent::Selected);

	Reflection::Instance()
		.add<TransformComponent>("TransformComponent")
		.addBase<Component>()
		.addProperty("Position", &TransformComponent::Position)
		.addProperty("Rotation", &TransformComponent::Rotation);
}
