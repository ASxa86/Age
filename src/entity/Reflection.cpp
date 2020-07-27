#include <azule/core/Reflection.h>
#include <azule/entity/AnimationComponent.h>
#include <azule/entity/CloneSystem.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/SelectionComponent.h>
#include <azule/entity/TransformComponent.h>
#include <azule/utilities/StaticInvoke.h>

using namespace azule::core;
using namespace azule::entity;

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

	Reflection::Instance().add<SelectionComponent>("SelectionComponent").addBase<Component>().addProperty("Selected", &SelectionComponent::Selected);

	Reflection::Instance()
		.add<TransformComponent>("TransformComponent")
		.addBase<Component>()
		.addProperty("Position", &TransformComponent::Position)
		.addProperty("Rotation", &TransformComponent::Rotation);
}
