#include <age/physics/KinematicComponent.h>

using namespace age::physics;

KinematicComponent::KinematicComponent() : Component()
{
	this->addProperty(this->BodyType, "BodyType");
	this->addProperty(this->CalculateHeading, "CalculateHeading");
	this->addProperty(this->LinearVelocity, "LinearVelocity");
}
