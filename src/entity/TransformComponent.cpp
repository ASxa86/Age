#include <azule/entity/TransformComponent.h>

using namespace azule;

TransformComponent::TransformComponent() : Component()
{
	this->addProperty("Position", this->Position);
	this->addProperty("Rotation", this->Rotation);
}
