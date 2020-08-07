#include <azule/physics/CircleCollisionComponent.h>

using namespace azule;

CircleCollisionComponent::CircleCollisionComponent() : CollisionComponent()
{
	this->addProperty("Radius", this->Radius);
}
