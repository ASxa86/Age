#include <azule/physics/KinematicComponent.h>

using namespace azule;

KinematicComponent::KinematicComponent() : Component()
{
	this->addProperty("LinearVelocity", this->LinearVelocity);
	this->addProperty("BodyType", this->BodyType);
	this->addProperty("CalculateHeading", this->CalculateHeading);
}
