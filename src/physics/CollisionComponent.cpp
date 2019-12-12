#include <age/physics/CollisionComponent.h>

using namespace age::physics;

CollisionComponent::CollisionComponent() : age::entity::Component()
{
	this->addProperty(this->Restitution, "Restitution");
	this->addProperty(this->Friction, "Friction");
	this->addProperty(this->Density, "Density");
	this->addProperty(this->IsSensor, "IsSensor");
}
