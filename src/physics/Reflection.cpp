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
	Reflection::Instance().add<KinematicComponent>("KinematicComponent").addBase<age::entity::Component>();
	Reflection::Instance().add<BoxCollisionComponent>("BoxCollisionComponent").addBase<age::entity::Component>();
	Reflection::Instance().add<CircleCollisionComponent>("CircleCollisionComponent").addBase<age::entity::Component>();
}
