#include <age/core/Reflection.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/CircleCollisionComponent.h>
#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsRenderSystem.h>
#include <age/physics/PhysicsSystem.h>
#include <age/physics/export.h>
#include <age/utilities/StaticInvoke.h>

using namespace age::core;
using namespace age::physics;

STATIC_INVOKE
{
	Reflection::Instance().add<PhysicsSystem>("PhysicsSystem").addBase<age::entity::System>();
	Reflection::Instance().add<PhysicsRenderSystem>("PhysicsRenderSystem").addBase<age::entity::System>();

	Reflection::Instance()
		.add<KinematicComponent>("KinematicComponent")
		.addBase<age::entity::Component>()
		.addProperty("BodyType", &KinematicComponent::BodyType)
		.addProperty("LinearVelocity", &KinematicComponent::LinearVelocity)
		.addProperty("CalculateHeading", &KinematicComponent::CalculateHeading);

	Reflection::Instance().add<BoxCollisionComponent>("BoxCollisionComponent").addBase<age::entity::Component>();

	Reflection::Instance()
		.add<CollisionComponent>("CollisionComponent")
		.addBase<age::entity::Component>()
		.addProperty("Restitution", &CollisionComponent::Restitution)
		.addProperty("Friction", &CollisionComponent::Friction)
		.addProperty("Density", &CollisionComponent::Density)
		.addProperty("IsSensor", &CollisionComponent::IsSensor);

	Reflection::Instance()
		.add<CircleCollisionComponent>("CircleCollisionComponent")
		.addBase<CollisionComponent>()
		.addProperty("Radius", &CircleCollisionComponent::Radius);
}
