#include <azule/physics/CollisionComponent.h>

using namespace azule;

CollisionComponent::CollisionComponent() : azule::Component()
{
	this->addProperty("Restitution", this->Restitution);
	this->addProperty("Friction", this->Friction);
	this->addProperty("Density", this->Density);
	this->addProperty("IsSensor", this->IsSensor);
}
