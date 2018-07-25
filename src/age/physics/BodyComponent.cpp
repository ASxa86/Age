#include <age/physics/BodyComponent.h>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <age/physics/PhysicsSystem.h>

using namespace age::physics;

BodyComponent::BodyComponent(PhysicsSystem& x)
{
	b2BodyDef def;
	this->body = x.getWorld().CreateBody(&def);
}

BodyComponent::~BodyComponent()
{
	this->body->GetWorld()->DestroyBody(this->body);
}
