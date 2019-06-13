#include <age/entity/TransformComponent.h>

using namespace age::entity;

TransformComponent::TransformComponent() : Component()
{
	this->addProperty(this->Position, "Position");
	this->addProperty(this->Rotation, "Rotation");
}
