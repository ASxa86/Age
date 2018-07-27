#include <age/physics/BodyComponent.h>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <age/entity/Entity.h>
#include <age/physics/PhysicsSystem.h>

using namespace age::physics;

BodyComponent::BodyComponent(PhysicsSystem& x, age::entity::Entity* e)
{
	b2BodyDef def;
	this->body = x.getWorld().CreateBody(&def);
	this->body->SetUserData(reinterpret_cast<void*>(e));
}

BodyComponent::~BodyComponent()
{
	this->body->GetWorld()->DestroyBody(this->body);
}
