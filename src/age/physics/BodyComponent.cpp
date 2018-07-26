#include <age/physics/BodyComponent.h>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <age/entity/Entity.h>
#include <age/physics/PhysicsSystem.h>

#ifdef WIN32
// Setting an int as void* for UserData within b2body
#pragma warning(disable : 4311 4312 4302)
#endif

using namespace age::physics;

BodyComponent::BodyComponent(PhysicsSystem& x, const age::entity::Entity& e)
{
	b2BodyDef def;
	this->body = x.getWorld().CreateBody(&def);
	this->body->SetUserData(reinterpret_cast<void*>(e.getID()));
}

BodyComponent::~BodyComponent()
{
	this->body->GetWorld()->DestroyBody(this->body);
}
