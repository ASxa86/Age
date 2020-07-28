#include <azule/core/Reflection.h>
#include <azule/physics/BoxCollisionComponent.h>
#include <azule/physics/CircleCollisionComponent.h>
#include <azule/physics/KinematicComponent.h>
#include <azule/physics/PhysicsRenderSystem.h>
#include <azule/physics/PhysicsSystem.h>
#include <azule/export.h>
#include <azule/utilities/StaticInvoke.h>

using namespace azule::core;
using namespace azule::physics;

STATIC_INVOKE
{
	Reflection::Instance().add<PhysicsSystem>("PhysicsSystem").addBase<azule::entity::System>();
	Reflection::Instance().add<PhysicsRenderSystem>("PhysicsRenderSystem").addBase<azule::entity::System>();

	Reflection::Instance()
		.add<KinematicComponent>("KinematicComponent")
		.addBase<azule::entity::Component>()
		.addProperty("BodyType", &KinematicComponent::BodyType)
		.addProperty("LinearVelocity", &KinematicComponent::LinearVelocity)
		.addProperty("CalculateHeading", &KinematicComponent::CalculateHeading);

	Reflection::Instance().add<BoxCollisionComponent>("BoxCollisionComponent").addBase<azule::entity::Component>();

	Reflection::Instance()
		.add<CollisionComponent>("CollisionComponent")
		.addBase<azule::entity::Component>()
		.addProperty("Restitution", &CollisionComponent::Restitution)
		.addProperty("Friction", &CollisionComponent::Friction)
		.addProperty("Density", &CollisionComponent::Density)
		.addProperty("IsSensor", &CollisionComponent::IsSensor);

	Reflection::Instance()
		.add<CircleCollisionComponent>("CircleCollisionComponent")
		.addBase<CollisionComponent>()
		.addProperty("Radius", &CircleCollisionComponent::Radius);
}
