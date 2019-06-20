#include <age/core/Factory.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/Export.h>
#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>

AGE_PHYSICS_EXPORT_C void FactoryRegister()
{
	AgeFactoryRegister(age::physics::PhysicsSystem).addBaseType<age::entity::System>();
	AgeFactoryRegister(age::physics::KinematicComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::physics::BoxCollisionComponent).addBaseType<age::entity::Component>();
}
